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
    , m_ifNamePort("")
{
}

TtyPort::TtyPort(const std::string &_path)
    : m_fd(-1)
    , m_ifNamePort(_path)
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
    if (IsOpen())
    {
        ::close(m_fd);
        m_fd = -1;
    }
}

int TtyPort::Read(char *_data, size_t _size, int _timeOut, std::string &_errorDescription)
{
    _errorDescription.clear();
    // TODO _errorDescription

    if (!IsOpen())
    {
        return -1;
    }

    struct pollfd fd; 
    fd.fd = m_fd;
    fd.events = POLLIN;

    int ret = ::poll(&fd, 1, _timeOut);
    if (ret < 0)
    {
        if (errno == EINTR)
        {
            return 0;
        }
        return -1;
    }
    else if (ret == 0)  // таймаут
    {
        return 0;
    }

    if (fd.revents & POLLIN) 
    {
        ssize_t bytes = ::read(m_fd, _data, _size);
        
        if (bytes < 0) 
        {
            if (errno == EINTR)
            {
                return 0;
            }
            return -1;
        }
        return static_cast<int>(bytes);
    }

    // что то пошло не так
    if (fd.revents & (POLLERR | POLLHUP | POLLNVAL))
    {
        return -1;
    }

    return 0;
}

bool TtyPort::Write(std::string_view _data, std::string &_errorDescription)
{
    if (!IsOpen())
    {
        return false;
    }

    _errorDescription.clear();
    // TODO написать errorDescription

    size_t total = 0;
    while (total < _data.size())
    {
        ssize_t res = ::write(m_fd, _data.data() + total, _data.size() - total);
        if (res < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }

            // переполнение буфера
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                struct pollfd fd;
                fd.fd = m_fd;
                fd.events = POLLOUT;

                int ret = ::poll(&fd, 1, 100);
                
                // что то пошло не так
                if (ret < 0 && errno == EINTR) 
                {
                    continue;
                }

                if (ret > 0 && (fd.revents & POLLOUT)) // осовобилось, продолжаем
                {
                    continue;
                }

                return false; // что то пошло не так
            }

            return false; // что то пошло нетак
        }

        // на всякий случай
        if (res == 0)
        {
            continue;
        }

        total += static_cast<size_t>(res);
    }

    return true;
}

bool TtyPort::IsOpen() const
{
    return m_fd != -1;
}

std::string TtyPort::GetPortName() const
{
    return m_ifNamePort;
}
