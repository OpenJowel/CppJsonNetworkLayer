#ifndef SOCKET_H
#define SOCKET_H

#include <string>


const unsigned MAXPACKETSIZE = 1 << 12;


class Socket
{
public:

	Socket();
	Socket(int fd);
	~Socket();

    int fd() const;
    bool isAlive() const;

    void sendString(const std::string& message);
    std::string receiveString();

    void kill();

protected:

    int m_fd;
    bool m_isAlive;

};

#endif	// SOCKET_H

