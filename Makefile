CC = g++
CFLAGS = -g -Wall

INC=./include

MAIN=./src/*

main:
	$(CC) $(CFLAGS) -I$(INC) $(MAIN)