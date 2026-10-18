#ifndef RULE_TABLE_H
#define RULE_TABLE_H

#include <string>
#include <vector>


struct EntryRule
{
    std::string expect;    // AT, ATE[1,0],  ATI, AT+COPS, AT+CPIN и т.д.
    std::string answer;    // ответы 
};

class RuleTable
{
private:
    std::vector<EntryRule>  m_rules;   

public:
    RuleTable() = default;
    ~RuleTable() = default;

    bool LoadFileRule(const std::string &_pathRule, std::string &_errorDescription);
};

#endif // RULE_TABLE_H