#include "rule_table.h"
#include "../common.h"
#include "../log.h"
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
    return true;
}

bool RuleTable::ParseRuleEntry(std::string_view _str, EntryRule &_rule, std::string &_errorDescription)
{
    return false;
}