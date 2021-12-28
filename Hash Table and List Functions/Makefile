CC = clang 
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all : l h

l: l.o 
	$(CC) -o l ltest.c List.c 

l.o: ltest.c List.c 
	$(CC) $(CFLAGS) -c ltest.c
	$(CC) $(CFLAGS) -c List.c
h: h.o 
	$(CC) -o h htest.c HashTable.c

h.o: htest.c HashTable.c 
	$(CC) $(CFLAGS) -c htest.c
	$(CC) $(CFLAGS) -c HashTable.c
clean:
	rm -f l *.o
	rm -f h *.o

format:
	$ clang-format -i -style=file List.c
	$ clang-format -i -style=file HashTable.c


