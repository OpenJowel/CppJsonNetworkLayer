#ifndef SOCKET_H
#define SOCKET_H

#include <string>


#define MAXPACKETSIZE 4096


class Socket
{
public:

	Socket();
	Socket(int fd);
	~Socket();

    int fd() const;
    bool isAlive() const;

    void sendString(std::string& message) const;
    std::string receiveString();

private:

    int m_fd;
    mutable bool m_isAlive;

};

#endif	// SOCKET_H

