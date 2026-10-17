#include "tty_port.h"
#include "../log.h"
#include "../common.h"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <poll.h>
#include <iostream>
#include <cstring>
#include <cerrno>

TtyPort::TtyPort()
    : m_fd(-1)
{
}

TtyPort::TtyPort(const std::string &_path)
    : m_fd(-1)
{
    Open(_path);
}

TtyPort::~TtyPort()
{
    Close();
}

bool TtyPort::Open(const std::string &_path)
{
    m_fd = ::open(_path.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (m_fd < 0)
    {
        Logger::Instance().ToConsole(StringFormat("%s : %s", __METHOD_NAME__, strerror(errno)));
        return false;
    }

    struct termios tty;
    if (tcgetattr(m_fd, &tty) != 0)
    {
        Logger::Instance().ToConsole(StringFormat("%s : tcgetattr failed: %s", __METHOD_NAME__, strerror(errno)));
        Close();
        return false;
    }

    // настройки
    cfmakeraw(&tty);
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CLOCAL | CREAD;
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 0;

    // записываем
    if (tcsetattr(m_fd, TCSANOW, &tty) != 0)
    {
        Logger::Instance().ToConsole(StringFormat("%s : tcsetattr failed: %s", __METHOD_NAME__, strerror(errno)));
        Close();
        return false;
    }

    Logger::Instance().ToConsole(StringFormat("%s : port %s opened successfully", __METHOD_NAME__, _path.c_str()));
    return true;
}

void TtyPort::Close()
{
    if (m_fd >= 0)
    {
        ::close(m_fd);
        m_fd = -1;
    }
}

int TtyPort::Read(char *_data, size_t _size, int _timeOut)
{
    return 0;
}

bool TtyPort::Write(std::string_view _data)
{
    return false;
}

bool TtyPort::IsOpen() const
{
    return m_fd != -1;
}
