simulator:	simulator.o Queue.o PriorityQueue.o 
	cc -o prog2 simulator.o Queue.o PriorityQueue.o

simulator.o: Queue.h Heap.h PriorityQueue.h simulator.c 
	cc -c simulator.c

Queue.o: Queue.h Queue.c
	cc -c Queue.c




PriorityQueue.o: Heap.h PriorityQueue.h Heap.c PriorityQueue.c
	cc -c PriorityQueue.c

clean:
	rm -f simulator simulator.o Queue.o Heap.o PriorityQueue.o prog2

check: 
	valgrind --leak-check=full ./prog2
