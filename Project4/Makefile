GPP=g++
CFLAGS=-Wall -std=c++14 -g -O0 -pedantic-errors

all: main
sorting.o: Sorting.cpp
	$(GPP) $(CFLAGS) -c Sorting.cpp

main: Sorting.o
	$(GPP) -o main Sorting.o

clean:
	rm -rf *.o

run:
	./main