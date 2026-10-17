#ifndef COMMON_H
#define COMMON_H
#include <string>

#define __METHOD_NAME__ MethodName(__PRETTY_FUNCTION__).c_str()

std::string DateTimeNow();
std::string ShowCommandHelp();
std::string StringFormat(const char *format, ...);
std::string MethodName(const std::string &_prettyFunction);


#endif // COMMON_H