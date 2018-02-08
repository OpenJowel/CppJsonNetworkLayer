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

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

	bool setup();
    void startAccepting();
    std::queue<Query> collectQueries();
    void removeDisconnected();

    void sendResponses(std::queue<Response>& responses);
    void terminate();

private:
    void broadcastString(std::string message) const;
    void sendStringTo(Client* client, std::string message) const;

    void acceptTask();

    mutable std::mutex m_clientsMutex;
    std::set<Client*> m_clients;

    std::thread m_acceptTask;

    int serverSocketFd;
    bool m_running;
};

#endif // TCPSERVER_H
