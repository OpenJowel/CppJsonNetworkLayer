/*
  This class is an example of application
*/


#ifndef APP_H
#define APP_H

#include <queue>
#include <string>
#include <unordered_map>
#include <functional>
#include <unistd.h>

#include "TcpServer.hpp"
#include "JsonTool.hpp"
#include "QueryResponseStructs.hpp"

class App
{
    // Type definitions
    typedef std::function<void(Client* source, Json::Value& queryRoot)> Callback;
    typedef std::unordered_map<std::string, Callback> Callbacks;

public:
    // Constructor / Destructor
	App();
	~App();

    // Methods

    // Initializes the callback functions
    void initCallbacks();

    // Starts the reception thread
    void start();

    // Treats all the queries from the server
    void treatQueries(std::queue<Query> queries);

    // The main program loop
    void mainLoop();

private:
    bool m_ready;
    bool m_running;
    TcpServer m_tcpServer;
    Callbacks m_callbacks;
    std::queue<Response> m_responses;
    std::string m_allMessages;
    JsonTool& m_jsonTool;

};

#endif	// APP_H

