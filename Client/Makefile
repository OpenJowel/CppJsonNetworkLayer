all: client

client: Socket.hpp Socket.cpp JsonUtils.cpp JsonUtils.hpp
	g++ -Wall -o client client.cpp TCPClient.cpp Socket.cpp JsonUtils.cpp -std=c++11 -lpthread -ljsoncpp

clean:
	rm -rf client

Socket.hpp :
	ln -s ../Socket.hpp Socket.hpp

Socket.cpp :
	ln -s ../Socket.cpp Socket.cpp

JsonUtils.hpp :
	ln -s ../JsonUtils.hpp JsonUtils.hpp

JsonUtils.cpp :
	ln -s ../JsonUtils.cpp JsonUtils.cpp


run: all
	./client

