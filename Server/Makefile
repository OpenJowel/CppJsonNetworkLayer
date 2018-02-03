all: server

run: all
	./server

clean:
	rm -rf *.o

TcpServer.o : TcpServer.cpp TcpServer.hpp
	g++ -g -c TcpServer.cpp -o TcpServer.o

Socket.o : Socket.cpp Socket.hpp
	g++ -g -c Socket.cpp -o Socket.o

JsonUtils.o : JsonUtils.cpp JsonUtils.hpp
	g++ -g -c JsonUtils.cpp -o JsonUtils.o

Client.o : Client.cpp Client.hpp
	g++ -g -c Client.cpp -o Client.o

SafeQueue.o : SafeQueue.cpp SafeQueue.hpp
	g++ -g -c SafeQueue.cpp -o SafeQueue.o

main.o : main.cpp
	g++ -g -c main.cpp -o main.o

Socket.hpp :
	ln -s ../Socket.hpp Socket.hpp

Socket.cpp :
	ln -s ../Socket.cpp Socket.cpp

JsonUtils.hpp :
	ln -s ../JsonUtils.hpp JsonUtils.hpp

JsonUtils.cpp :
	ln -s ../JsonUtils.cpp JsonUtils.cpp

server : Socket.hpp Socket.cpp TcpServer.o Socket.o Client.o SafeQueue.o JsonUtils.o main.o
	g++ -g -o server TcpServer.o Socket.o Client.o SafeQueue.o JsonUtils.o main.o -std=c++11 -lpthread -ljsoncpp

