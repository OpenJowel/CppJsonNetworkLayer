#ifndef RECEIVETASK_H
#define RECEIVETASK_H

#include <queue>
#include <string>
#include <thread>

#include "Socket.hpp"
#include "SafeQueue.hpp"

#include "QueryResponseStructs.hpp"

class Client
{
public:
	Client(int socketFd);
	~Client();

    int socketFd() const;

    // negative quantity = get all
    std::queue<Query> queries(int quantity = -1);

    void send(std::string& data) const;

    bool hasFinished() const;

    void start();
    void stop();

private:
    void receiveTask();
    void closeSocket();

    std::thread m_receiveTask;
    Socket m_socket;

    SafeQueue m_queries;
};

#endif	// RECEIVETASK_H

