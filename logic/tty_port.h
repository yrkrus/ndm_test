#ifndef TTY_PORT_H
#define TTY_PORT_H
#include <string>
#include <string_view>
#include <termios.h>

enum class BaudRate
{
   ecRate9600, 
   ecRate19200,
   ecRate38400,
   ecRate57600,
   ecRate115200, // Стандарт де-факто для AT-команд
   ecRate230400,
   ecRate460800,
   ecRate921600, 
};

inline speed_t ToSpeed(BaudRate _rate)
{
   switch (_rate)
   {
   case BaudRate::ecRate9600:    return B9600;
   case BaudRate::ecRate19200:   return B19200;
   case BaudRate::ecRate38400:   return B38400;
   case BaudRate::ecRate57600:   return B57600;
   case BaudRate::ecRate115200:  return B115200;
   case BaudRate::ecRate230400:  return B230400;
   case BaudRate::ecRate460800:  return B460800;
   case BaudRate::ecRate921600:  return B921600;
   default:                      return B115200;
   }
}

class TtyPort
{
private:
   int         m_fd;
   std::string m_ifNamePort;
   BaudRate    m_speed;

public:
   TtyPort(const std::string &_path, BaudRate _speed);
   ~TtyPort();

   TtyPort(const TtyPort &) = delete;
   TtyPort &operator=(const TtyPort &) = delete;

   bool Open(const std::string &_path, BaudRate _speed);
   void Close();

   int Read(char *_data, size_t _size, int _timeOut, std::string &_errorDescription);
   bool Write(std::string_view _data, std::string &_errorDescription);

   bool IsOpen() const;
   std::string GetPortName() const;
};

#endif // TTY_PORT_H