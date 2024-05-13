CC = g++
CFLAGS = -g -Wall -std=c++11 -pedantic


MAIN=./src/*.cpp

main:
	$(CC) $(CFLAGS) -I./include -L./lib -o a.exe $(MAIN) -lglfw3dll -lopengl32