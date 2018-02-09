/*
  Client derives from Socket and implements a thread dedicated to the reception
*/

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
    // Constructor / Destructor
	Client(int socketFd);
	~Client();

    // negative quantity = get all
    std::queue<Query> queries(int quantity = -1);


private:
    //Methods

    // Starts the reception thread
    void start();

    // Method called in the thread
    void receiveTask();

    // Attributes
    std::thread m_receiveTask;
    SafeQueue m_safeQueriesQueue;
};

#endif	// RECEIVETASK_H

