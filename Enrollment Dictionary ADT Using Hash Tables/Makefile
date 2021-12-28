CC = clang 
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all : prog3

prog3: prog3.o 
	$(CC) -o prog3 List.c HashTable.c Dictionary.c Enrollment.c 

prog3.o: HashTable.c List.c Enrollment.c Dictionary.c 
	$(CC) $(CFLAGS) -c HashTable.c
	$(CC) $(CFLAGS) -c List.c
	$(CC) $(CFLAGS) -c Dictionary.c
	$(CC) $(CFLAGS) -c Enrollment.c
clean:
	rm -f prog3 *.o

format:
	$ clang-format -i -style=file List.c
	$ clang-format -i -style=file HashTable.c
	$ clang-format -i -style=file Enrollment.c
	$ clang-format -i -style=file Dictionary.c


