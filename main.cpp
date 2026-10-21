// Тестовое задание 
// Реализуйте приложение-сервер на с/с++, 
// который прослушивает tty устройство и отвечает на AT команды.

// Словарь ожиданий в виде ограниченного синтаксиса 
// регулярных выражений (точка - один любой символ, * - ноль или любой символ)  и ответов к ним
// разместить в csv файле или текстовом файле expect=answer.
// Базовый тестовый набор команд: AT, ATE[1,0],  ATI, AT+COPS, AT+CPIN.

// Нельзя использовать библиотеку для разбора регулярных выражений в решении.
#include <iostream>
#include "common.h"
#include "config.h"
#include "log.h"
#include "logic/tty_port.h"
#include "logic/at_server.h"
#include "logic/rule_table.h"


int main(int argc, char *argv[])
{
    if (argc < config::cMinCommand) 
    {
        ShowCommandHelp(argv[0]);
        return 1;    
    }

    std::string tty_port    = config::cTTYPath;
    ConnectionSpeed speed   = config::cDefaultSpeed;
    std::string ruleList    = config::cRuleTableFile;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-t")
        {
            if (i + 1 < argc) { tty_port = argv[++i]; }
            else { /* ошибка */ return 1; }
        }
        else if (arg == "-p")
        {
            if (i + 1 < argc)
            {
                int tmp = 0;
                if (!IsValidNumber(argv[++i], tmp))
                {
                    Logger::Instance().ToConsole("main() : port value is not a valid");
                    return 1;
                }

                speed = IntToEnum(tmp);
                if (speed == ConnectionSpeed::ecUnknown)
                {
                    Logger::Instance().ToConsole("main() : port speed is not supported");
                    return 1;
                }
            }
            else { /* ошибка */ return 1; }
        }
        else if (arg == "-r")
        {
            if (i + 1 < argc) { ruleList = argv[++i]; }
            else { /* ошибка */ return 1; }
        }
        else 
        {
            Logger::Instance().ToConsole(StringFormat("main() : unknown argument %s", arg.c_str()));
            return 1;
        }
    }

    //ruleList
    std::string errorDescription;
    RuleTable rule;
    if(!rule.LoadFileRule(ruleList, errorDescription))  
    {
        Logger::Instance().ToConsole(StringFormat("main() : rule table error : %s", errorDescription.c_str()));
        return 1;
    }
   
    // tty_port и speed
    TtyPort port(tty_port, speed);
    if (!port.IsOpen()) 
    {
        Logger::Instance().ToConsole(StringFormat("main() : port opening '%s' error ", tty_port.c_str()));
        return 1;
    }

    // run server
    ATServer server(rule, port);
    server.Start();

    return 0;
}