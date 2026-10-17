#include "common.h"
#include <chrono>
#include <ctime>
#include <cstdio>
#include <string>
#include <cstdarg>

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

std::string ShowCommandHelp()
{
    return std::string();
}

const std::string StringFormat(const char* format, ...)
{
    char buffer[1024] = {};
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
