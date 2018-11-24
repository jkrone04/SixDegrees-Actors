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
