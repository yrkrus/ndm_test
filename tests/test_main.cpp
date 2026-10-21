#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "../logic/rule_table.h"
#include "../common.h"

// проваленые тесты
int g_failed = 0;

#define EXPECT(condition, test_name) \
    do { \
        if (condition) { \
            std::cout << "[  OK  ] " << test_name << "\n"; \
        } else { \
            std::cerr << "[ FAIL ] " << test_name << "\n"; \
            g_failed++; \
        } \
    } while(0)

void TestMatch() 
{
    std::cout << "--- Testing RuleTable::Match ---\n";

    // Базовые совпадения
    EXPECT(RuleTable::Match("AT", "AT") == true, "Exact match 'AT'");
    EXPECT(RuleTable::Match("AT", "AX") == false, "Mismatch 'AT' vs 'AX'");

    // Точка (.)
    EXPECT(RuleTable::Match("ATE.", "ATE0") == true, "Dot matches one char");
    EXPECT(RuleTable::Match("ATE.", "ATE1") == true, "Dot matches one char");
    EXPECT(RuleTable::Match("ATE.", "ATE") == false, "Dot requires exactly one char");
    EXPECT(RuleTable::Match("A.T", "AXT") == true, "Dot in the middle");

    // Звездочка (*)
    EXPECT(RuleTable::Match("*", "AT+COPS?") == true, "Star matches everything");
    EXPECT(RuleTable::Match("*", "") == true, "Star matches empty string");
    EXPECT(RuleTable::Match("AT*", "AT") == true, "Star matches zero chars");
    EXPECT(RuleTable::Match("AT*", "ATE0") == true, "Star matches multiple chars");
    EXPECT(RuleTable::Match("A*T", "AT") == true, "Star in middle, zero chars");
    EXPECT(RuleTable::Match("A*T", "ABCDEFGT") == true, "Star in middle, many chars");
    EXPECT(RuleTable::Match("A*T", "ABCDEFG") == false, "Star in middle, no ending char");

    // Сложные случаи
    EXPECT(RuleTable::Match("AT+CPIN=\"*\"", "AT+CPIN=\"1234\"") == true, "CPIN with star");
    EXPECT(RuleTable::Match("AT+CPIN=\"*\"", "AT+CPIN=\"\"") == true, "CPIN with empty quotes");
}

void TestParseRuleEntry()
{
    std::cout << "--- Testing RuleTable::ParseRuleEntry ---\n";
    std::string err;
    
    // Валидная строка
    EntryRule rule1;
    EXPECT(RuleTable::ParseRuleEntry("AT=OK\\r\\n", rule1, err) == true, "Parse valid rule");
    EXPECT(rule1.expect == "AT", "Parsed expect correctly");
    EXPECT(rule1.answer == "OK\r\n", "Replaced \\r\\n correctly"); // \r\n

    // Невалидные строки
    EntryRule rule2;
    EXPECT(RuleTable::ParseRuleEntry("ATOK", rule2, err) == false, "Parse missing '='");
    EXPECT(RuleTable::ParseRuleEntry("=OK", rule2, err) == false, "Parse empty expect");
    EXPECT(RuleTable::ParseRuleEntry("AT=", rule2, err) == false, "Parse empty answer");
}

void TestIsValidNumber()
{
    std::cout << "--- Testing IsValidNumber ---\n";
    int val = 0;

    EXPECT(IsValidNumber("115200", val) == true, "Parse valid number");
    EXPECT(val == 115200, "Number value is correct");
    EXPECT(IsValidNumber("abc", val) == false, "Parse string (invalid)");
    EXPECT(IsValidNumber("123abc", val) == false, "Parse mixed string (invalid)");
    EXPECT(IsValidNumber("-9600", val) == true, "Parse negative number");
    EXPECT(IsValidNumber("", val) == false, "Parse empty string");
}

int main()
{
    std::cout << "Starting tests...\n\n";
    
    TestMatch();
    std::cout << "\n";
    TestParseRuleEntry();
    std::cout << "\n";
    TestIsValidNumber();

    std::cout << "\n=========================\n";
    if (g_failed == 0)
    {
        std::cout << "ALL TESTS PASSED SUCCESSFULLY!\n";
        return 0;
    }
    else
    {
        std::cerr << "FAILED TESTS: " << g_failed << "\n";
        return 1;
    }
}