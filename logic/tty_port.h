#ifndef TTY_PORT_H
#define TTY_PORT_H
#include <string>
#include <string_view>
#include <termios.h>

enum class ConnectionSpeed
{
   ecUnknown = 0,   // чисто для проверки только
   ec9600, 
   ec19200,
   ec38400,
   ec57600,
   ec115200, // Стандарт де-факто для AT-команд
   ec230400,
   ec460800,
   ec921600,    
};

inline speed_t ToSpeed(ConnectionSpeed _speed)
{
   switch (_speed)
   {
   case ConnectionSpeed::ec9600:    return B9600;
   case ConnectionSpeed::ec19200:   return B19200;
   case ConnectionSpeed::ec38400:   return B38400;
   case ConnectionSpeed::ec57600:   return B57600;
   case ConnectionSpeed::ec115200:  return B115200;
   case ConnectionSpeed::ec230400:  return B230400;
   case ConnectionSpeed::ec460800:  return B460800;
   case ConnectionSpeed::ec921600:  return B921600;
   default:                         return B115200;
   }
}

inline uint EnumToInt(ConnectionSpeed _speed) 
{
   switch (_speed)
   {
   case ConnectionSpeed::ec9600:    return 9600;
   case ConnectionSpeed::ec19200:   return 19200;
   case ConnectionSpeed::ec38400:   return 38400;
   case ConnectionSpeed::ec57600:   return 57600;
   case ConnectionSpeed::ec115200:  return 115200;
   case ConnectionSpeed::ec230400:  return 230400;
   case ConnectionSpeed::ec460800:  return 460800;
   case ConnectionSpeed::ec921600:  return 921600;
   default:                         return 0;
   }  
}

inline ConnectionSpeed IntToEnum(int _speed) 
{
   switch (_speed)
   {
   case 9600:    return ConnectionSpeed::ec9600;    
   case 19200:   return ConnectionSpeed::ec19200;
   case 38400:   return ConnectionSpeed::ec38400;
   case 57600:   return ConnectionSpeed::ec57600;
   case 115200:  return ConnectionSpeed::ec115200;
   case 230400:  return ConnectionSpeed::ec230400;
   case 460800:  return ConnectionSpeed::ec460800;
   case 921600:  return ConnectionSpeed::ec921600;
   default:      return ConnectionSpeed::ecUnknown;
   }  
}

class TtyPort
{
private:
   int                  m_fd;
   std::string          m_ifNamePort;
   ConnectionSpeed      m_speed;

public:
   TtyPort(const std::string &_path, ConnectionSpeed _speed);
   ~TtyPort();

   TtyPort(const TtyPort &) = delete;
   TtyPort &operator=(const TtyPort &) = delete;

   bool Open(const std::string &_path, ConnectionSpeed _speed);
   void Close();

   int Read(char *_data, size_t _size, int _timeOut, std::string &_errorDescription);
   bool Write(std::string_view _data, std::string &_errorDescription);

   bool IsOpen() const;
   std::string GetPortName() const;
};

#endif // TTY_PORT_H