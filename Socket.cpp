#include "Socket.hpp"

#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <cstdint>
#include <unistd.h>

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
    cout << "Destroying socket" << endl;
    close(m_fd);
}

int Socket::fd() const
{
    return m_fd;
}

bool Socket::isAlive() const
{
    return m_isAlive;
}

void Socket::sendString(const string& message)
{
    // Sending header
    HeaderType messageLength = message.size();
    //if(send(m_fd, &messageLength, sizeof(HeaderType), 0) < sizeof(HeaderType)){
    if(send(m_fd, &messageLength, sizeof(HeaderType), MSG_NOSIGNAL) < sizeof(HeaderType)){
        kill();
        return;
    }

    // Sending data
    //if(send(m_fd, message.c_str(), messageLength, 0) < messageLength){
    if(send(m_fd, message.c_str(), messageLength, MSG_NOSIGNAL) < messageLength){
        kill();
    }
}

string Socket::receiveString()
{
    string message = "";

    // Get header
    HeaderType messageLength = 0;
    if(recv(m_fd, &messageLength, sizeof(HeaderType), 0) > 0 && messageLength <= MAXPACKETSIZE){

        vector<char> buffer;
        buffer.resize(messageLength);

        // Get data
        HeaderType receivedBytes = 0;
        HeaderType newQuantity = 0;

        do{
            newQuantity = recv(m_fd, &buffer[0], messageLength - receivedBytes, 0);
            receivedBytes += newQuantity;
        }
        while(receivedBytes < messageLength && receivedBytes > 0 && newQuantity > 0);

        message = string(buffer.begin(), buffer.end());

    }
    else{
        kill();
    }

    return message;
}

void Socket::kill()
{
    cout << "Killing client" << endl;
    m_isAlive = false;
}
