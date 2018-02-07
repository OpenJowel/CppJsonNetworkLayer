all: client

client: Socket.o JsonTool.o TcpClient.o main.o
	g++ -Wall -o client Socket.o JsonTool.o TcpClient.o main.o -std=c++11 -lpthread -ljsoncpp

clean:
	rm -rf client
	rm -rf *.o

main.o : main.cpp
	g++ -c main.cpp -o main.o

TcpClient.o : TcpClient.cpp TcpClient.hpp
	g++ -c TcpClient.cpp -o TcpClient.o

Socket.o : Socket.cpp Socket.hpp
	g++ -c Socket.cpp -o Socket.o

JsonTool.o : JsonTool.cpp JsonTool.hpp
	g++ -c JsonTool.cpp -o JsonTool.o

Socket.hpp :
	ln -s ../Socket.hpp Socket.hpp

Socket.cpp :
	ln -s ../Socket.cpp Socket.cpp

JsonTool.hpp :
	ln -s ../JsonTool.hpp JsonTool.hpp

JsonTool.cpp :
	ln -s ../JsonTool.cpp JsonTool.cpp


run: all
	./client

