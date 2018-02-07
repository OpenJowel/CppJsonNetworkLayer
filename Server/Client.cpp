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

bool Client::hasFinished() const
{
    return !isAlive();
}

void Client::receiveTask()
{
    cout << "I'm task for socket " << m_fd << endl;

    while(isAlive()){
        m_queries.push({receiveString(), this});
    }

    cout << "Finished receive task for " << m_fd << endl;
}

void Client::send(std::string& data) const
{
    sendString(data);
}

void Client::start()
{
    m_receiveTask = thread([this]{this->receiveTask();});
    m_receiveTask.detach();
}

void Client::stop()
{
    cout << "Stopping client task" << endl;
    //closeSocket();
}

/*
void Client::closeSocket()
{
    //close(m_socket.fd());
}
*/
