#
# File: Makefile
#



PROGRAMS = rexp

CFLAGS = -g -std=c99 -Wall -Werror

programs: $(PROGRAMS)

rexp: Tree.o RecursiveDescent.o Production.o TableDriven.o ExpressionTree.o main.o LinkedList.o
	$(CC) -o $@ $^

LinkedList:
	$(CC) -o $@ $(CFLAGS) -DMAIN $@.c

clean:
	-rm $(PROGRAMS) *.o

run:
	./rexp

check:
	valgrind --leak-check=full ./rexp
