#include "Client.hpp"

#include <iostream>
#include <unistd.h>

#include "Socket.hpp"

using namespace std;

Client::Client(int socketFd):
    Socket(socketFd)
{
    start();
}

Client::~Client()
{
    cout << "Destruction of client" << endl;
}

queue<Query> Client::queries(int quantity)
{
    return m_queries.elements(quantity);
}

void Client::receiveTask()
{
    int fd = m_fd;
    cout << "I'm task for socket " << m_fd << endl;

    while(isAlive()){
        m_queries.push({receiveString(), this});
    }

    cout << "Finished receive task for " << fd << endl;
}

void Client::send(std::string& data)
{
    sendString(data);
}

void Client::start()
{
    m_receiveTask = thread([this]{this->receiveTask();});
    m_receiveTask.detach();
}

