/*
  This class implements a TCP server process that handles client connections
  Messages from clients can be collected in order to process them further in the application
*/

#ifndef TCPSERVER_H
#define TCPSERVER_H

//#include <cstddef>
#include <set>
#include <netinet/in.h>
#include <thread>
#include <mutex>

#include "Client.hpp"
#include "Socket.hpp"

#include "QueryResponseStructs.hpp"

const unsigned CLIENTPACKETSBYFRAME = 1;

class TcpServer
{
public:

    //Methods

    // Initializes the server and starts listening
	bool setup();

    // Starts the client acceptation thread
    void startAccepting();

    // Returns a queue of clients queries
    std::queue<Query> collectQueries();

    // Deletes disconnected clients from the set
    void removeDisconnected();

    // Send the responses to clients
    void sendResponses(std::queue<Response>& responses);

    // Finishes server execution
    void terminate();

private:

    // Structures
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    // Send a string to all clients
    void broadcastString(std::string message) const;

    // Send a string to a given client
    void sendStringTo(Client* client, std::string message) const;

    // Method called in the thread
    void acceptTask();
    std::thread m_acceptTask;

    mutable std::mutex m_clientsMutex;
    std::set<Client*> m_clients;

    int serverSocketFd;
    bool m_running;
};

#endif // TCPSERVER_H
