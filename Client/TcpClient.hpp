#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netdb.h> 
#include <vector>

#include "Socket.hpp"

class TcpClient
{

public:
    TcpClient();
    bool setup(std::string address, int port);
    bool Send(std::string data);
    std::string receive();

private:
    std::string address;
    int m_port;
    struct sockaddr_in m_server;
    Socket* m_socket;

};

#endif    //TCPCLIENT_H
