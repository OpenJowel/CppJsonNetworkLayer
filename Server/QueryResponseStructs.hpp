#ifndef QUERYRESPONSESTRUCTS_H
#define QUERYRESPONSESTRUCTS_H

#include <string>

class Client;

struct Query{
    std::string data;
    Client* source;
};

struct Response
{
    std::string data;
    Client* target = nullptr;
};

#endif	// QUERYRESPONSESTRUCTS_H

