CC = clang 
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all : prog1

prog1: prog1.o 
	$(CC) -o prog1 prog1.c List.c 

prog1.o: prog1.c List.c
	$(CC) $(CFLAGS) -c prog1.c
	$(CC) $(CFLAGS) -c List.c
clean:
	rm -f prog1 *.o

format:
	$ clang-format -i -style=file prog1.c
	$ clang-format -i -style=file List.c

checkProg1:
	valgrind --leak-check=full ./prog1 


