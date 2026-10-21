#include "common.h"
#include "config.h"
#include <chrono>
#include <ctime>
#include <cstdio>
#include <string>
#include <cstdarg>
#include <iostream>

std::string DateTimeNow()
{
    using namespace std::chrono;

    auto now = system_clock::now();
    auto secs = time_point_cast<seconds>(now);
    auto ms = duration_cast<milliseconds>(now - secs).count();

    std::time_t t = system_clock::to_time_t(now);
    std::tm tm{};
    localtime_r(&t, &tm);

    char buff[32];
    std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", &tm);

    char res[40];
    std::snprintf(res, sizeof(res), "%s.%03lld", buff, (long long)ms);
    
    return res;
}

void ShowCommandHelp(const char *_progname)
{
    std::cout << "Usage: " << _progname << " -t [tty_path] -p [port_speed] -r [rules_file]\n"
              << "\nDefaults:\n"
              << "  tty_path     : " << config::cTTYPath << "\n"
              << "  port_speed   : " << EnumToInt(config::cDefaultSpeed) << "\n"
              << "  rules_file   : " << config::cRuleTableFile << "\n\n";
}

std::string StringFormat(const char* format, ...)
{
    char buffer[config::cMaxBuffStringFormat] = {};
    va_list ap;

    va_start(ap, format);
    vsnprintf(buffer, sizeof(buffer), format, ap);
    va_end(ap);

    return std::string(buffer);
}

std::string MethodName(const std::string &_prettyFunction)
{
    const size_t colons = _prettyFunction.find("::");
    const size_t begin = _prettyFunction.substr(0,colons).rfind(" ") + 1;
    const size_t count = _prettyFunction.rfind("(") - begin;
    const std::string tempResult{_prettyFunction, begin, count};
    
    size_t space = tempResult.rfind(" ");
    static const char *cBraces = "()";
    if (space == std::string::npos)
    {
        return tempResult + cBraces;
    }

    return tempResult.substr(space + 1, tempResult.size() - space - 1) + cBraces;
}

bool IsValidNumber(const std::string &_str, int &_result)
{
    if (_str.empty())
    {
        return false;
    }

    try
    {
        size_t pos = 0;
        int value = std::stoi(_str, &pos);

        if (pos != _str.length())
        {
            return false;
        }

        _result = value;
        return true;
    }
    catch (const std::invalid_argument &)
    {
        return false; // В строке вообще нет цифр (например, "hello")
    }
    catch (const std::out_of_range &)
    {
        return false; // Число слишком большое (например, "99999999999999999999")
    }
}
