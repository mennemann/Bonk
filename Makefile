CC = g++
CFLAGS = -g -Wall

INC=./include

MAIN=./src/main.cpp

main:
	$(CC) $(CFLAGS) -I$(INC) $(MAIN)