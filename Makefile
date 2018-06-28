all: main

main: main.o
	g++ -o main main.o

main.o: main.cpp
	g++ -std=c++11 -c -o main.o main.cpp

clean:
	rm main.o
