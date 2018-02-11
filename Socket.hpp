/*
  Manages the emission and reception of packets through TCP protocol
*/

#ifndef SOCKET_H
#define SOCKET_H

#include <string>

const unsigned MAXPACKETSIZE = 1 << 16;

class Socket
{
public:

    // Constructors / Destructor
	Socket();
	Socket(int fd);
	~Socket();

    //Getters
    // Tells if the socket is still alive
    bool isAlive() const;

    //Methods

    // Send the given string to the peer
    void sendString(const std::string& message);

    // Returns a received string from peer
    std::string receiveString();

    void kill();

protected:

    int m_fd;
    bool m_isAlive;

};

#endif	// SOCKET_H

