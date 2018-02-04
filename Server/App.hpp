#ifndef APP_H
#define APP_H

#include <queue>
#include <string>
#include <unordered_map>
#include <functional>
#include <unistd.h>

#include "TcpServer.hpp"
#include "JsonUtils.hpp"
#include "QueryResponseStructs.hpp"

class App
{
    typedef std::function<void(Client* source, Json::Value& queryRoot)> Callback;
    typedef std::unordered_map<std::string, Callback> Callbacks;

public:
	App();
	~App();
    void initCallbacks();
    void start();
    void treatQueries(std::queue<Query> queries);
    void mainLoop();

private:
    bool m_ready;
    bool m_running;
    TcpServer m_tcpServer;
    Callbacks m_callbacks;
    std::queue<Response> m_responses;
    std::string m_allMessages;
    JsonUtils m_jsonUtils;

};

#endif	// APP_H

