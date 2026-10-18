// Тестовое задание 
// Реализуйте приложение-сервер на с/с++, 
// который прослушивает tty устройство и отвечает на AT команды.

// Словарь ожиданий в виде ограниченного синтаксиса 
// регулярных выражений (точка - один любой символ, * - ноль или любой символ)  и ответов к ним
// разместить в csv файле или текстовом файле expect=answer.
// Базовый тестовый набор команд: AT, ATE[1,0],  ATI, AT+COPS, AT+CPIN.

// Нельзя использовать библиотеку для разбора регулярных выражений в решении.
#include <iostream>
#include "main_inc.h"

int main(int argc, char *argv[])
{
    // TODO сделать
    // if (argc < config::cMinCommand) 
    // {
    //     ShowCommandHelp();
    //     return 1;    
    // }
    
    // load rule
    std::string errorDesription;
    RuleTable rule;
    if(!rule.LoadFileRule(config::cRuleTableFile, errorDesription))  
    {
        Logger::Instance().ToConsole(StringFormat("main() : rule table error : %s", errorDesription.c_str()));
        return 1;
    }
   
    // try open tty port
    TtyPort port(config::cTTYPath, BaudRate::ecRate115200);
    if (!port.IsOpen()) 
    {
        Logger::Instance().ToConsole(StringFormat("main() : port opening '%s' error ", config::cTTYPath.c_str()));
        return 1;
    }

    // run server
    ATServer server(rule, port);
    server.Start();


    return 0;
}