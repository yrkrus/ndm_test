#include "at_server.h"
#include "../config.h"
#include "../log.h"
#include "../common.h"
#include <iostream>

#define DATA_BUFF 256

ATServer::ATServer(RuleTable &_rule, TtyPort &_port)
    : m_rule(_rule) 
    , m_port(_port)
    , m_running(false)
{
}

void ATServer::Start()
{
    m_running = true;
    char buff[DATA_BUFF];
    Logger::Instance().ToConsole(StringFormat("%s : server successfully started on port %s", 
                                                __METHOD_NAME__, m_port.GetPortName().c_str()));

    while (m_running)
    {
        std::string errorDescription;
        int ret = m_port.Read(buff, sizeof(buff), config::cTimeOutAtServerReadData, errorDescription);
        if (ret > 0)
        {
            m_buffer.append(buff, ret);

            // ищем конец строки
            size_t pos = 0;
            while ((pos = m_buffer.find_first_of(config::cCRLF)) != std::string::npos)
            {
                std::string command = m_buffer.substr(0, pos);
                m_buffer.erase(0, pos + 1);

                if (!command.empty())
                {
                    ExecuteCommand(command);
                }
            }
        }
        else if (ret < 0)
        {
            m_running = false;
            Logger::Instance().ToConsole(StringFormat("%s : server stopped on port %s error %s", 
                                                        __METHOD_NAME__, 
                                                        m_port.GetPortName().c_str(),
                                                        errorDescription.c_str()));
        }
    }
}

void ATServer::Stop()
{
    m_running = false;
    Logger::Instance().ToConsole(StringFormat("%s : server stopped on port %s", 
                                                __METHOD_NAME__, m_port.GetPortName().c_str()));
}

void ATServer::ExecuteCommand(const std::string &_str)
{
    Logger::Instance().ToConsole(StringFormat("RX: [%s]", _str.c_str()));

    std::string response = m_rule.FindAnswer(_str);
    if (response.empty()) 
    {
        response = "ERROR";
        response += config::cCRLF;
        Logger::Instance().ToConsole("TX: [ERROR] (Rule not found)");
    }
    else 
    {
        Logger::Instance().ToConsole(StringFormat("TX: [%s]", response.c_str()));
    }
    
    std::string errorDescription;
    if (!m_port.Write(response, errorDescription))
    {
        Logger::Instance().ToConsole(StringFormat("%s : %s", __METHOD_NAME__, errorDescription.c_str()));
    }
}
