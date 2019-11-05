# Grammar-Parsing
Implements both a recursive-descent parser and a table-driven parser for the grammar of regular expressions. Also creates an expression tree to print regular expressions in prefix notation.

The executable file is named rexp. You may run ./rexp after manually compiling the files, or you may follow the instructions below.

To create the executable file, use the terminal while in the project directory and run:
	make

After that, you can run the program by running:
	make run

To clean the repository, run:
	make clean

You can use valgrind:
	make check

My project does not have any memory leaks--all heap blocks were freed at exit.

**************************************
LinkedList.ch: LinkedList implementation (not mine)  
Tree.ch: Tree implementation for the parse tree and the expression tree  
RecursiveDescent.ch: Functions for Part 1  
TableDriven.ch: Functions for Part 2  
Production.ch: Production implementation to store our grammar  
ExpressionTree.ch: Functions for Part 3  
main.c: Runs a REPL loop that terminates on EOF, specified to the user as Ctrl + D.  
      Creates the grammar, an array of productions, to be used by the parsing table.  
      For each user input, either print "Invalid expression" or print the results to Part 1-3. There will be two identical parse trees, and the expression in prefix notation.
