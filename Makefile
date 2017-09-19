CC=g++
CCFLAGS=-std=c++11

all: tictactoe
	make clean

tictactoe: main.o
	$(CC) main.o -o tictactoe

main.o: main.cpp
	$(CC) $(CCFLAGS) -c main.cpp

clean:
	rm main.o
