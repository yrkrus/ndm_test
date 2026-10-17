#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <string_view>

namespace config 
{
    static const std::string cLogFileName = "log.log";
    static const std::string cTTYPath  = "/dev/pts/3";
    constexpr const char cMinCommand = 3;
    constexpr const uint8_t cTimeOutAtServerReadData = 200;
    inline constexpr std::string_view cCRLF = "\r\n";
}

#endif // CONFIG_H