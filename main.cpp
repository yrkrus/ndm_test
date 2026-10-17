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
    
   
    TtyPort port(config::cTTYPath);
    if (!port.IsOpen()) 
    {
        Logger::Instance().ToConsole(StringFormat("port opening '%s' error ", config::cTTYPath.c_str()));
        return 1;
    }

    ATServer server(port);
    server.Start();


    std::cout << "hello\n";
    return 0;
}