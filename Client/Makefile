all: client

client: Socket.o JsonUtils.o TcpClient.o main.o
	g++ -Wall -o client Socket.o JsonUtils.o TcpClient.o main.o -std=c++11 -lpthread -ljsoncpp

clean:
	rm -rf client
	rm -rf *.o

main.o : main.cpp
	g++ -c main.cpp -o main.o

TcpClient.o : TcpClient.cpp TcpClient.hpp
	g++ -c TcpClient.cpp -o TcpClient.o

Socket.o : Socket.cpp Socket.hpp
	g++ -c Socket.cpp -o Socket.o

JsonUtils.o : JsonUtils.cpp JsonUtils.hpp
	g++ -c JsonUtils.cpp -o JsonUtils.o

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

