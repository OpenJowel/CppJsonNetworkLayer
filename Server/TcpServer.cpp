#include "TcpServer.hpp" 

#include <iostream>
#include <unistd.h>
#include <string.h>

#include <json/value.h>

#include "JsonUtils.hpp"

using namespace std;

bool TcpServer::setup(int port)
{
    serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if(!serverSocketFd){
        return false;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);

    if(bind(serverSocketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
        cout << "Could not bind to port " << port << endl;
        return false;
    }

    if(listen(serverSocketFd, CLIENTSMAXQUANTITY) < 0){
        cout << "Could not start listening" << endl;
        return false;
    }

    m_running = true;

    return m_running;
}

void TcpServer::startAccepting()
{
    m_acceptTask = thread([this]{this->acceptTask();});
    m_acceptTask.detach();
}

void TcpServer::acceptTask()
{
    JsonUtils jsonUtils;
    while(m_running){
        socklen_t sosize = sizeof(clientAddress);
        int newSocketFd = accept(serverSocketFd, (struct sockaddr*)&clientAddress, &sosize);

        cout << "Client connection attempt" << endl;
        Client* client = new Client(newSocketFd);

        if(m_clients.size() < CLIENTSMAXQUANTITY){
            cout << "New client joined !" << endl;
            m_clientsMutex.lock();
            m_clients.insert(client);
            m_clientsMutex.unlock();
        }
        else{
            cout << "Rejected connection" << endl;
            Json::Value errorMessage;
            errorMessage["requestType"] = "errorMessage";
            errorMessage["message"] = "Server is full";
            sendStringTo(client, jsonUtils.valueToJsonString(errorMessage));
            client->stop();
            //delete client;
        }
    }
}

queue<Query> TcpServer::collectQueries()
{
    queue<Query> messages;

    //lock_guard<mutex> lock(m_clientsMutex);
    m_clientsMutex.lock();
    for(Client* client: m_clients){
        queue<Query> clientQueries = client->queries(CLIENTPACKETSBYFRAME);
        while(!clientQueries.empty()){
            messages.push(clientQueries.front());
            clientQueries.pop();
        }
    }
    m_clientsMutex.unlock();

    return messages;
}

void TcpServer::removeDisconnected()
{
    set<Client*>::iterator it = m_clients.begin();

    //lock_guard<mutex> lock(m_clientsMutex);
    m_clientsMutex.lock();
    while(it != m_clients.end()){
        Client* client = *it;
        if(client->hasFinished()){
            cout << "Closing " << client->socketFd() << endl;
            client->stop();
            //delete client;
            client = nullptr;
            it = m_clients.erase(it);
        }
        else{
            it++;
        }
    }
    m_clientsMutex.unlock();
}

void TcpServer::sendResponses(std::queue<Response>& responses)
{
    while(!responses.empty()){
        Response& response = responses.front();

        if(response.target){
            sendStringTo(response.target, response.data);
        }
        else{
            broadcastString(response.data);
        }

        responses.pop();
    }
}

void TcpServer::broadcastString(string message) const
{
    lock_guard<mutex> lock(m_clientsMutex);
    for(Client* client : m_clients){
        sendStringTo(client, message);
    }
}

void TcpServer::sendStringTo(Client* client, string message) const
{
    client->send(message);
}

void TcpServer::closeSockets()
{
    close(serverSocketFd);

    for(Client* client : m_clients){
        client->stop();
    }
}


void TcpServer::terminate()
{
    m_running = false;

    closeSockets();

    cout << "Server finished peacefully" << endl;
}
