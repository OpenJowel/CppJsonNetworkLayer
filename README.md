# CppJsonNetworkLayer
##This is an easy-to-use TCP server implementation in order to communicate with JSON strings

This layer offers the ability to send/receive string messages encoded in JSON format between a server and multiple clients.

The Json layer requires JsonCpp

Provided classes are :

##Socket :
Implements a dynamic-size message send/receive communication using AF/INET sockets

##Client :
    Derives from sockets and implements a thread dedicated to messages reception
    
##TcpServer :
    Provides a client-acception thread and collects queries from clients
    
##SafeQueue
    Concurrent-proof queue storing queries

##App
    Gives an example of application that runs an instance of TcpServer and answers to client queries

Extra classes :

##Config :
    Provides the ability to read the configuration of the server from an external file

##JsonTool :
    A class that interfaces JsonCpp to make it very straightforward to use


The Client program is just for debug.
Because the code between client and server is very symetrical in the principle, a smoother client implementation can easily be done using above classes.
