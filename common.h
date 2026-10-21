#ifndef COMMON_H
#define COMMON_H
#include <string>

#define __METHOD_NAME__ MethodName(__PRETTY_FUNCTION__).c_str()

std::string DateTimeNow();
void ShowCommandHelp(const char *_progname);
std::string StringFormat(const char *format, ...);
std::string MethodName(const std::string &_prettyFunction);
bool IsValidNumber(const std::string &_str, int &_result); 



#endif // COMMON_H