all: main

main: main.o gaussian.o
	g++ -o main main.o gaussian.o

main.o: main.cpp
	g++ -c main.cpp

gaussian.o: gaussian.cpp
	g++ -c gaussian.cpp

clean:
	rm -f main *.o 