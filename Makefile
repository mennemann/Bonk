CC = g++
CFLAGS = -g -Wall -std=c++11


MAIN=./src/*.cpp

main:
	$(CC) $(CFLAGS) -I./include -L./lib $(MAIN) -lglfw3dll