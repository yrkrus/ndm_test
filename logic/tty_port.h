#ifndef TTY_PORT_H
#define TTY_PORT_H
#include <string>
#include <string_view>

class TtyPort
{
 private:
    int m_fd;

 public:  
    TtyPort();
    TtyPort(const std::string &_path);
    ~TtyPort();

    TtyPort(const TtyPort&) = delete;
    TtyPort& operator=(const TtyPort&) = delete;

    bool Open(const std::string &_path);
    void Close();

    int Read(char *_data, size_t _size, int _timeOut = 1000);
    bool Write(std::string_view _data);

    bool IsOpen() const;
};

#endif // TTY_PORT_H