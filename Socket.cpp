#include "Socket.hpp"

#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;
using HeaderType = int32_t;

Socket::Socket():
    m_fd(0),
    m_isAlive(false)
{

}

Socket::Socket(int fd):
    m_fd(fd),
    m_isAlive(true)
{

}

Socket::~Socket()
{

}

int Socket::fd() const
{
    return m_fd;
}

bool Socket::isAlive() const
{
    return m_isAlive;
}

void Socket::sendString(string& message) const
{
    // Sending header
    HeaderType messageLength = message.size();
    if(send(m_fd, &messageLength, sizeof(HeaderType), MSG_NOSIGNAL) < sizeof(HeaderType)){
        m_isAlive = false;
        return;
    }

    // Sending data
    if(send(m_fd, message.c_str(), messageLength, MSG_NOSIGNAL) < messageLength){
        m_isAlive = false;
    }
}

string Socket::receiveString()
{
    string message = "";

    // Get header
    HeaderType messageLength = 0;
    if(0 < recv(m_fd, &messageLength, sizeof(HeaderType), 0) && messageLength <= MAXPACKETSIZE){

        vector<char> buffer;
        buffer.resize(messageLength);

        // Get data
        HeaderType receivedBytes = 0;
        while(receivedBytes < messageLength){
            receivedBytes += recv(m_fd, &buffer[0], messageLength - receivedBytes, 0);
        }

        message = string(buffer.begin(), buffer.end());

    }
    else{
        m_isAlive = false;
    }

    return message;
}

