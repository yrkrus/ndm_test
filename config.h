#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <string_view>

namespace config 
{
    static const std::string cLogFileName               = "log.log";
    constexpr const uint16_t cMaxBuffStringFormat       = 1024;
    static const std::string cTTYPath                   = "/dev/pts/2";
    constexpr const char cMinCommand                    = 3;
    constexpr const uint8_t cTimeOutAtServerReadData    = 200;
    inline constexpr std::string_view cCRLF             = "\r\n";
    static const std::string cRuleTableFile             = "rules";

}

#endif // CONFIG_H