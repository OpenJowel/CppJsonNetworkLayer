#include "Client.hpp"

#include <iostream>
#include <unistd.h>

#include "Socket.hpp"

using namespace std;

Client::Client(int socketFd):
    m_socket(socketFd)
{
    start();
}

Client::~Client()
{
    cout << "Destruction of client" << endl;
}

int Client::socketFd() const
{
    return m_socket.fd();
}

queue<Query> Client::queries(int quantity)
{
    return m_queries.elements(quantity);
}

bool Client::hasFinished() const
{
    return !m_socket.isAlive();
}

void Client::receiveTask()
{
    cout << "I'm task for socket " << m_socket.fd() << endl;

    while(m_socket.isAlive()){
        m_queries.push({m_socket.receiveString(), this});
    }

    cout << "Finished receive task for " << m_socket.fd() << endl;
}

void Client::send(std::string& data) const
{
    m_socket.sendString(data);
}

void Client::start()
{
    m_receiveTask = thread([this]{this->receiveTask();});
    m_receiveTask.detach();
}

void Client::stop()
{
    cout << "Stopping client task" << endl;
    closeSocket();
}

void Client::closeSocket()
{
    close(m_socket.fd());
}
