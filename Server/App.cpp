#include "App.hpp"

#include <iostream>
#include <unistd.h>

using namespace std;

App::App():
    m_ready(false),
    m_running(false),
    m_tcpServer(),
    m_jsonTool(JsonTool::getInstance())
{
    initCallbacks();
    m_ready = m_tcpServer.setup();
}

App::~App()
{

}

void App::initCallbacks(){
    m_callbacks["publicMessage"] = [this](Client* client, Json::Value& queryRoot){

        string message = queryRoot["message"].asString();
        m_allMessages += " " + message;
        cout << "received public message : '" << message << "'" << endl;

        Json::Value responseRoot;
        responseRoot["requestType"] = "message";
        responseRoot["message"] = m_allMessages;

        Response response;
        response.target = nullptr;
        response.data = m_jsonTool.valueToJsonString(responseRoot);

        m_responses.push(response);
    };

    m_callbacks["privateMessage"] = [this](Client* client, Json::Value& queryRoot){

        string message = queryRoot["message"].asString();
        cout << "received private message : '" << message << "'" << endl;

        Json::Value responseRoot;
        responseRoot["requestType"] = "message";
        responseRoot["message"] = message;

        Response response;
        response.target = client;
        response.data = m_jsonTool.valueToJsonString(responseRoot);

        m_responses.push(response);
    };

}

void App::start()
{
    if(!m_ready){
        cout << "Could not start application. TCP server is not ready" << endl;
        return;
    }

    m_running = true;
    m_tcpServer.startAccepting();

    mainLoop();
}

void App::treatQueries(queue<Query> queries)
{
    Json::Value queryRoot;
    string requestType;

    while(!queries.empty()){
        Query& query = queries.front();

        queryRoot = m_jsonTool.jsonStringToValue(query.data);

        if(!queryRoot.empty() && queryRoot.isMember("requestType")){
            requestType = queryRoot["requestType"].asString();

            if(m_callbacks.find(requestType) != m_callbacks.end()){
                m_callbacks[queryRoot["requestType"].asString()](query.source, queryRoot);
            }
            else{
                query.source->kill();
            }
        }
        else{
            query.source->kill();
        }

        queries.pop();
    }
}

void App::mainLoop()
{
    while(m_running){
        m_tcpServer.removeDisconnected();
        queue<Query> queries = m_tcpServer.collectQueries();

        treatQueries(queries);

        m_tcpServer.sendResponses(m_responses);

        usleep(100000);

    }

    m_tcpServer.terminate();
}

