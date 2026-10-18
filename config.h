#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <string_view>

namespace config 
{
    inline const std::string cLogFileName               = "log.log";
    constexpr const uint16_t cMaxBuffStringFormat       = 1024;
    inline const std::string cTTYPath                   = "/dev/pts/2";
    constexpr const uint8_t cMinCommand                 = 3;
    constexpr const uint8_t cTimeOutAtServerReadData    = 200;
    inline constexpr std::string_view cCRLF             = "\r\n";
    inline const std::string cRuleTableFile             = "rules.txt";
}

#endif // CONFIG_H