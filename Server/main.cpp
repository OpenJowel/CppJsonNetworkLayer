#include <iostream>
#include <thread>

#include <unistd.h>

#include <unordered_map>
#include <functional>

#include "TcpServer.hpp"
#include "JsonUtils.hpp"

TcpServer tcp;

using namespace std;
bool running = true;

queue<Response> responses;

string allMessages = "";

JsonUtils jsonUtils;

unordered_map<string, function<void(Client* source, Json::Value& queryRoot)>> callbacks;


void initCallbacks(){
    callbacks["publicMessage"] = [](Client* client, Json::Value& queryRoot){
        
        string message = queryRoot["message"].asString();
        allMessages += " " + message;
        cout << "received public message : '" << message << "'" << endl;

        Json::Value responseRoot;
        responseRoot["requestType"] = "message";
        responseRoot["message"] = allMessages;

        Response response;
        response.target = nullptr;
        response.data = jsonUtils.valueToJsonString(responseRoot);

        responses.push(response);
    };

    callbacks["privateMessage"] = [](Client* client, Json::Value& queryRoot){
        
        string message = queryRoot["message"].asString();
        cout << "received private message : '" << message << "'" << endl;
        
        Json::Value responseRoot;
        responseRoot["requestType"] = "message";
        responseRoot["message"] = message;

        Response response;
        response.target = client;
        response.data = jsonUtils.valueToJsonString(responseRoot);

        responses.push(response);
    };

}

void treatQueries(queue<Query> queries)
{
    Json::Value queryRoot;

    while(!queries.empty()){
        Query& query = queries.front();

        queryRoot = jsonUtils.jsonStringToValue(query.data);

        if(!queryRoot.empty()){
            callbacks[queryRoot["requestType"].asString()](query.source, queryRoot);
        }

        queries.pop();
    }
}

void mainLoop()
{
    while(running){
        tcp.removeDisconnected();
        queue<Query> queries = tcp.collectQueries();

        treatQueries(queries);

        tcp.sendResponses(responses);

        usleep(100000);
    }
}

int main()
{
    int port = 13337;

    if(!tcp.setup(port)){
        return 0;
    }

    initCallbacks();

    tcp.startAccepting();

    mainLoop();


    tcp.terminate();

    return 0;
}
