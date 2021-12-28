all : prog0

prog0: prog0.o 
	gcc -Wall -o prog0 prog0.o 

prog0.o: prog0.c
	gcc -Wall -c -g  prog0.c

clean:
	rm -f prog0 *.o

checkProg0:
	valgrind --leak-check=full ./prog0 -i test2

format:
	$ clang-format -i -style=file prog0.c



