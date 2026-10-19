#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <string_view>
#include <cstdint>

namespace config 
{
    inline const std::string cLogFileName               = "log.log";
    constexpr const uint16_t cMaxBuffStringFormat       = 1024;
    inline const std::string cTTYPath                   = "/dev/pts/37";
    constexpr const uint8_t cMinCommand                 = 3;
    constexpr const uint8_t cTimeOutAtServerReadData    = 200;
    inline constexpr std::string_view cCRLF             = "\r\n";
    inline const std::string cRuleTableFile             = "/home/yrkrus/projects/_code/ndm_test/rules.txt";
}

#endif // CONFIG_H