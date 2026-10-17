#ifndef AT_SERVER_H
#define AT_SERVER_H
#include "tty_port.h"
#include <atomic>

class ATServer
{
private:
    TtyPort             &m_port; 
    std::atomic<bool>   m_running;
    std::string         m_buffer;

    void ExecuteCommand(const std::string &_str);    

public:
    explicit ATServer(TtyPort &_port);

    void Start();
    void Stop();
};

#endif // AT_SERVER_H