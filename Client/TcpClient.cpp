#include "TcpClient.hpp"

using namespace std;

TcpClient::TcpClient()
{
	m_port = 0;
	address = "";
}

bool TcpClient::setup(string address , int port)
{
    int socketFd = -1;
    m_port = port;

  	if(socketFd == -1){
		socketFd = socket(AF_INET , SOCK_STREAM , 0);
		if (socketFd == -1){
      		cout << "Could not create socket" << endl;
    	}
    }

  	if(inet_addr(address.c_str()) == -1){
    	struct hostent *he;
    	struct in_addr **addr_list;

    	if((he = gethostbyname(address.c_str())) == NULL){
		     herror("gethostbyname");
             cout << "Failed to resolve hostname" << endl;
             return false;
    	}

        addr_list = (struct in_addr **) he->h_addr_list;
    	for(int i = 0; addr_list[i] != NULL; i++){
            m_server.sin_addr = *addr_list[i];
            break;
    	}
  	}
  	else{
        m_server.sin_addr.s_addr = inet_addr(address.c_str());
  	}

  	m_server.sin_family = AF_INET;
  	m_server.sin_port = htons(m_port);

  	if(connect(socketFd, (struct sockaddr *)&m_server, sizeof(m_server)) < 0){
        cout << ("connect failed. Error") << endl;
        return 1;
  	}

    cout << "init socket" << endl;
    m_socket = new Socket(socketFd);

  	return true;
}

bool TcpClient::Send(string data)
{
    m_socket->sendString(data);

    return true;
}

string TcpClient::receive()
{
    string message = "";

    message = m_socket->receiveString();

    return message;
}

