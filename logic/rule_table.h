#ifndef RULE_TABLE_H
#define RULE_TABLE_H

#include <string>
#include <vector>
#include <string_view>

struct EntryRule
{
    std::string expect; // AT, ATE[1,0],  ATI, AT+COPS, AT+CPIN и т.д.
    std::string answer; // ответы

    bool isValid() const
    {
        return !expect.empty() && !answer.empty(); // считаем что пустой что то из
    }
};

class RuleTable
{
private:
    std::vector<EntryRule>  m_rules;       
    static bool ParseRuleEntry(std::string_view _str, EntryRule &_rule, std::string &_errorDescription);
    static bool Match(std::string_view _pattern, std::string_view _command);

public:
    RuleTable() = default;
    ~RuleTable() = default;

    bool LoadFileRule(const std::string &_pathRule, std::string &_errorDescription);
    void Show();

    std::string FindAnswer(std::string_view _command) const;       
};

#endif // RULE_TABLE_H