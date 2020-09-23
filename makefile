CFLAGS = -std=c++11

all: Sender Receiver

Sender : Sender.cpp packet.cpp common.cpp
	g++ $(CFLAGS) Sender.cpp packet.cpp -o $@

Receiver : Receiver.cpp packet.cpp common.cpp
	g++ $(CFLAGS) Receiver.cpp packet.cpp -o $@