#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace config 
{
    static const std::string cLogFileName = "log.log";
    static const std::string cTTYPath  = "/dev/pts/32";
    constexpr const char cMinCommand = 3;
}

#endif // CONFIG_H