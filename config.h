#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <string_view>
#include <cstdint>
#include "logic/tty_port.h"

namespace config 
{
    inline constexpr const char *cLogFileName           = "log.log";
    inline constexpr const char *cTTYPath               = "/dev/pts/37";
    inline constexpr const char *cRuleTableFile         = "rules.txt";
    const ConnectionSpeed cDefaultSpeed                 = ConnectionSpeed::ec115200;
    constexpr const uint16_t cMaxBuffStringFormat       = 1024;
    constexpr const uint8_t cMinCommand                 = 2;
    constexpr const uint8_t cTimeOutAtServerReadData    = 200;
    inline constexpr std::string_view cCRLF             = "\r\n";
}

#endif // CONFIG_H