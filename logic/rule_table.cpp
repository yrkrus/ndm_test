#include "rule_table.h"
#include "../common.h"
#include "../log.h"
#include "../config.h"
#include <filesystem>
#include <cerrno>
#include <cstring>

namespace fs = std::filesystem;
static const char _commentPattern = '#';


bool RuleTable::LoadFileRule(const std::string &_pathRule, std::string &_errorDescription)
{
    _errorDescription.clear();
    m_rules.clear();

    if (!fs::exists(_pathRule))
    {
        _errorDescription = StringFormat("file rule '%s' not exist", _pathRule.c_str());
        return false;
    }

    std::ifstream fileRule(_pathRule);
    if (!fileRule.is_open())
    {
        _errorDescription = StringFormat("file rule '%s' not opened : %s", _pathRule.c_str(), strerror(errno));
        return false;
    }

    std::string stroka;
    while (std::getline(fileRule, stroka))
    {
        if (stroka.empty() || stroka.front() == _commentPattern)
        {
            continue;
        }

        EntryRule rule;
        if (!ParseRuleEntry(stroka, rule, _errorDescription))
        {
            // что то пошло нетак
            Logger::Instance().ToConsole(StringFormat("%s : %s", __METHOD_NAME__, _errorDescription.c_str()));
            continue;
        }

        if (!rule.isValid())
        {
            continue;
        }

        m_rules.push_back(std::move(rule));
    }

    if (m_rules.empty())
    {
        _errorDescription = StringFormat("the rules '%s' contains no rules", _pathRule.c_str());
        return false;
    }

    Logger::Instance().ToConsole(StringFormat("%s : loaded %zu rule", __METHOD_NAME__, m_rules.size()));
    // Show();
    return true;
}

void RuleTable::Show()
{
    for (const auto &[exp, ans] : m_rules)
    {
        printf("expect = %s\nanswer = %s", exp.c_str(), ans.c_str());
    }
}

bool RuleTable::ParseRuleEntry(std::string_view _str, EntryRule &_rule, std::string &_errorDescription)
{
    size_t pos = _str.find("=");
    if (pos == std::string_view::npos) 
    {
        _errorDescription = StringFormat("in rule '%s' no match separator", std::string(_str).c_str());
        return false;
    }

    if (pos == 0 || pos == _str.length() - 1)
    {
        _errorDescription = StringFormat("in rule '%s' empty expect or answer", std::string(_str).c_str());
        return false;
    }

    _rule.expect = std::string(_str.substr(0, pos));
    _rule.answer = std::string(_str.substr(pos + 1));
    
    // замена переносов \r\n  
    size_t repl_pos;
    while ((repl_pos = _rule.answer.find("\\r\\n")) != std::string::npos) 
    {
        _rule.answer.replace(repl_pos, 4, config::cCRLF.data(), config::cCRLF.size());           
    }
    
    // одночные на всякий случай
    while ((repl_pos = _rule.answer.find("\\r")) != std::string::npos) 
    {
        _rule.answer.replace(repl_pos, 2,"\r");           
    }
    while ((repl_pos = _rule.answer.find("\\n")) != std::string::npos) 
    {
        _rule.answer.replace(repl_pos, 2,"\n");           
    }

    return true;
}