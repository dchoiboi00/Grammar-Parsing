#
# File: Makefile
#



PROGRAMS = rexp

CFLAGS = -g -std=c99 -Wall -Werror

programs: $(PROGRAMS)

rexp: Tree.o RecursiveDescent.o main.o LinkedList.o
	$(CC) -o $@ $^

LinkedList:
	$(CC) -o $@ $(CFLAGS) -DMAIN $@.c

clean:
	-rm $(PROGRAMS) *.o
	-rm -r *.dSYM

run:
	./rexp

check:
	valgrind --leak-check=full ./rexp