#include <iostream>
#include "log.h"
#include "common.h"
#include "config.h"

#define DATE_TIME __DATE__ " " __TIME__

Logger::Logger(const std::string &_name)
    : m_name(_name)
{
    m_file.open(config::cLogFileName, std::ios::app);
    if (!m_file.is_open())
    {
        printf("Failed to open log file %s\n", config::cLogFileName.c_str());
    }
}

Logger::~Logger()
{
    if (m_file)
    {
        m_file.close();
    }
}

Logger &Logger::Instance()
{
    static Logger log(config::cLogFileName);
    return log;
}

void Logger::ToConsole(std::string_view _str, LogTarget _target)
{
    std::string timeStamp = DateTimeNow();
    std::cout << timeStamp << " : " << _str << "\n";

    if (_target == LogTarget::ecConsoleAndFile)
    {
        ToFile(_str, timeStamp);
    }
}

void Logger::ToFile(std::string_view _str, std::string_view timestamp)
{
    if (!m_file)
    {
        return;
    }

    m_file << timestamp << " : " << _str << "\n";
}

void Logger::ToFile(std::string_view _str)
{
    if (!m_file)
    {
        return;
    }
    m_file << DateTimeNow() << " : " << _str << "\n";
}
