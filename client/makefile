#NAME - ANKUSH NAGPAL   ROLL NO - 2018201083

# -*- MakeFile -*-

#target: dependencies
#	action


CC=g++
#all:  homepage ver_overflow


client:client.o functions.o
	$(CC) -std=c++11 client.o functions.o  -o client -lssl -lcrypto -pthread


client.o:client.cpp
	$(CC) -std=c++11 -c client.cpp functions.h

functions.o:functions.cpp
	$(CC) -std=c++11 -c functions.cpp

clear:
	rm *.o client 