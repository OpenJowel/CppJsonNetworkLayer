#include <iostream>
#include <string>
#include <sstream>

#include "TCPClient.h"
#include "JsonUtils.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	if(argc >= 2)
	{
		TCPClient tcp;
        JsonUtils jsonUtils;

		tcp.setup("127.0.0.1",13337);
		int num = atoi(argv[2]);
		cout << "Num Request:" << num <<endl;
		for(int i = 0; i < num; i++)
		{
            ostringstream str1;
            str1 << i;
            string iString = str1.str();

            Json::Value queryRoot;
            //queryRoot["requestType"] = "publicMessage";
            queryRoot["requestType"] = "privateMessage";
            queryRoot["message"] = string(argv[1]) + " " + iString;

            string query = jsonUtils.valueToJsonString(queryRoot);

			tcp.Send(query);
			string rec = tcp.receive();
			if( rec != "" )
			{
				cout << "Server Response:" << rec << endl;
			}
			sleep(1);
		}
		exit(0);
		return 0;
	}
	else cout << "Error: message num-request" << endl;
}
