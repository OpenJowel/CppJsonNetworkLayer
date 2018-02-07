#ifndef RECEIVETASK_H
#define RECEIVETASK_H

#include <queue>
#include <string>
#include <thread>

#include "Socket.hpp"
#include "SafeQueue.hpp"

#include "QueryResponseStructs.hpp"

class Client : public Socket
{
public:
	Client(int socketFd);
	~Client();

    // negative quantity = get all
    std::queue<Query> queries(int quantity = -1);

    void send(std::string& data);

    void start();

private:
    void receiveTask();
    std::thread m_receiveTask;
    SafeQueue m_queries;
};

#endif	// RECEIVETASK_H

