#ifndef LOG_H
#define LOG_H
#include <string>
#include <string_view>
#include <fstream>

enum class LogTarget 
{
    ecConsoleOnly,
    ecConsoleAndFile
};

class Logger
{
private:
    std::string m_name;
    std::ofstream m_file;

    explicit Logger(const std::string &_name);
    ~Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

public:
    static Logger &Instance();
    void ToConsole(std::string_view _str, LogTarget _target = LogTarget::ecConsoleOnly);
    void ToFile(std::string_view _str, std::string_view timestamp);
    void ToFile(std::string_view _str);
};

#endif // LOG_H