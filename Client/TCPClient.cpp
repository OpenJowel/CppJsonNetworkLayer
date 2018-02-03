#include "TCPClient.h"
#include "Socket.hpp"

TCPClient::TCPClient()
{
	m_socketFd = -1;
	port = 0;
	address = "";
}

bool TCPClient::setup(string address , int port)
{
  	if(m_socketFd == -1)
	{
		m_socketFd = socket(AF_INET , SOCK_STREAM , 0);
		if (m_socketFd == -1)
		{
      			cout << "Could not create socket" << endl;
    		}
        }
  	if(inet_addr(address.c_str()) == -1)
  	{
    		struct hostent *he;
    		struct in_addr **addr_list;
    		if ( (he = gethostbyname( address.c_str() ) ) == NULL)
    		{
		      herror("gethostbyname");
      		      cout<<"Failed to resolve hostname\n";
		      return false;
    		}
	   	addr_list = (struct in_addr **) he->h_addr_list;
    		for(int i = 0; addr_list[i] != NULL; i++)
    		{
      		      server.sin_addr = *addr_list[i];
		      break;
    		}
  	}
  	else
  	{
    		server.sin_addr.s_addr = inet_addr( address.c_str() );
  	}
  	server.sin_family = AF_INET;
  	server.sin_port = htons( port );
  	if (connect(m_socketFd, (struct sockaddr *)&server , sizeof(server)) < 0)
  	{
    		perror("connect failed. Error");
    		return 1;
  	}
  	return true;
}

bool TCPClient::Send(string data)
{
    Socket socket(m_socketFd);

    socket.sendString(data);
    
    return true;
}

string TCPClient::receive(int size)
{
    string message = "";

    Socket socket(m_socketFd);
    message = socket.receiveString();

    return message;
}

string TCPClient::read()
{
  	char buffer[1] = {};
  	string reply;
  	while (buffer[0] != '\n') {
    		if( recv(m_socketFd , buffer , sizeof(buffer) , 0) < 0)
    		{
      			cout << "receive failed!" << endl;
      			break;
    		}
		reply += buffer[0];
	}
	return reply;
}
