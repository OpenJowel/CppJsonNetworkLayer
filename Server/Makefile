all: server

run: all
	./server

clean:
	rm -rf *.o

TcpServer.o : TcpServer.cpp TcpServer.hpp
	g++ -g -c TcpServer.cpp -o TcpServer.o

Socket.o : Socket.cpp Socket.hpp
	g++ -g -c Socket.cpp -o Socket.o

JsonTool.o : JsonTool.cpp JsonTool.hpp
	g++ -g -c JsonTool.cpp -o JsonTool.o

Client.o : Client.cpp Client.hpp
	g++ -g -c Client.cpp -o Client.o

SafeQueue.o : SafeQueue.cpp SafeQueue.hpp
	g++ -g -c SafeQueue.cpp -o SafeQueue.o

App.o : App.cpp App.hpp
	g++ -g -c App.cpp -o App.o

main.o : main.cpp
	g++ -g -c main.cpp -o main.o

Socket.hpp :
	ln -s ../Socket.hpp Socket.hpp

Socket.cpp :
	ln -s ../Socket.cpp Socket.cpp

JsonTool.hpp :
	ln -s ../JsonTool.hpp JsonTool.hpp

JsonTool.cpp :
	ln -s ../JsonTool.cpp JsonTool.cpp

server : Socket.hpp Socket.cpp TcpServer.o Socket.o Client.o SafeQueue.o JsonTool.o App.o main.o
	g++ -g -o server TcpServer.o Socket.o Client.o SafeQueue.o JsonTool.o App.o main.o -std=c++11 -lpthread -ljsoncpp

