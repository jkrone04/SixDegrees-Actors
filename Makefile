# Jake Kroner
# COMP15
# Fall 2018
# Makefile for Trie

CC = clang++
CFLAGS = -Wall -Wextra -c -std=c++11
DEPS = SixDegrees.h Graph.h Actor.h LinkedList.h Queue.h Stack.h
 
 %.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

sixdegrees: main.o SixDegrees.o Graph.o Actor.o LinkedList.o Queue.o Stack.o
	$(CC) -o sixdegrees main.o SixDegrees.o Graph.o Actor.o LinkedList.o Queue.o Stack.o

graphtest: test-graph.o Graph.o Actor.o LinkedList.o Queue.o Stack.o
	$(CC) -o graphtest test-graph.o Graph.o Actor.o LinkedList.o Queue.o Stack.o

clean:
	rm -f *.o core* *~ sixdegrees, graphtest

provide:
	provide comp15 hw5 main.cpp Makefile Graph.h Graph.cpp Actor.h Actor.cpp SixDegrees.h SixDegrees.cpp test-graph.cpp README
