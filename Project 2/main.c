//
//  main.c
//  Project 2
//
//  Created by Daniel Choi on 10/2/19.
//  Copyright © 2019 Daniel Choi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RecursiveDescent.h"
#include "TableDriven.h"
#include "ExpressionTree.h"


int main(int argc, const char * argv[]) {
    char input[15];
    printf("CSC173 Project 2 by Yoo Choi\n");
    
    /*
     * Part 1: Recursive-Descent Parser
     */
    while (true){
        printf("\nEnter a regular expression (max 15 characters) to run a recursive-descent parser (\"quit\" to quit): ");
        scanf("%15s", input);   //take input
        
        if (strcmp(input, "quit") == 0){
            printf("Quit Part 1: Recursive-descent Parsing\n\n");
            break;
        }
        
        recursive_desc_parser(input);
    }
    /*
     * Part 2: Table-Driven Parser
     */
    Production E = new_Production("<E>");
    Production_add_to_body(E, "<C>", 1);
    Production_add_to_body(E, "<ET>", 1);
//    print_Production(E);
    
    Production ET = new_Production("<ET>");
    Production_add_to_body(ET, "|", 1);
    Production_add_to_body(ET, "<E>", 1);
    Production_add_to_body(ET, "", 2);
    
    Production C = new_Production("<C>");
    Production_add_to_body(C, "<S>", 1);
    Production_add_to_body(C, "<CT>", 1);
    
    Production CT = new_Production("<CT>");
    Production_add_to_body(CT, ".", 1);
    Production_add_to_body(CT, "<C>", 1);
    Production_add_to_body(CT, "", 2);
    
    Production S = new_Production("<S>");
    Production_add_to_body(S, "<A>", 1);
    Production_add_to_body(S, "<ST>", 1);
    
    Production ST = new_Production("<ST>");
    Production_add_to_body(ST, "*", 1);
    Production_add_to_body(ST, "<ST>", 1);
    Production_add_to_body(ST, "", 2);
//    print_Production(ST);
    
    Production A = new_Production("<A>");
    Production_add_to_body(A, "(", 1);
    Production_add_to_body(A, "<E>", 1);
    Production_add_to_body(A, ")", 1);
    Production_add_to_body(A, "<X>", 2);
    
    Production X = new_Production("<X>");
    char* alphabet[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    for (int i = 1; i < 27; i++){
        Production_add_to_body(X, alphabet[i-1], i);
    }
//    print_Production(X);
    
    //Create our grammar
    Production* grammar = (Production*)malloc(sizeof(Production) * 8);
    grammar[0] = E;
    grammar[1] = ET;
    grammar[2] = C;
    grammar[3] = CT;
    grammar[4] = S;
    grammar[5] = ST;
    grammar[6] = A;
    grammar[7] = X;
    int grammar_size = 8;
    
    int** table = create_parsing_table(grammar, grammar_size);
    
    while (true){
        printf("\nEnter a regular expression (max 15 characters) to run a table-driven parser (\"quit\" to quit): ");
        scanf("%15s", input);   //take input
        
        if (strcmp(input, "quit") == 0){
            printf("Quit Part 2: Table-driven Parsing\n\n");
            break;
        }
        
        Tree tree = table_driven_parser(input, table, grammar, grammar_size);
        printf("Inputed expression: %s\n", input);
        
        //if the tree is either NULL or if E() ended before the end of the string, print ERROR
        if (tree == NULL){
            printf("ERROR: Invalid expression\n");
        } else {  //otherwise, print our tree
            print_Tree(tree);
            free_Tree(tree);
        }
    }
    
    //Part 3: Build an expression tree, and print in prefix notation
    while (true){
        printf("\nEnter a regular expression (max 15 characters) to print its parse tree AND its expression tree in prefix notation (\"quit\" to quit): ");
        scanf("%15s", input);   //take input
        
        if (strcmp(input, "quit") == 0){
            printf("Quit Part 3: Expression Trees in Prefix Notation \n\n");
            break;
        }
        
        Tree tree = table_driven_parser(input, table, grammar, grammar_size);
        printf("Inputed expression: %s\n", input);
        
        //if the tree is either NULL or if E() ended before the end of the string, print ERROR
        if (tree == NULL){
            printf("ERROR: Invalid expression\n");
        } else {  //otherwise, print our tree
            print_Tree(tree);
            
            LinkedList stack = new_LinkedList();   //did not free
            createStack(tree, stack);
            LinkedList_print_string_list(stack);
            
            Tree expressionTree = createExpressionTree(stack);
            printPrefixExpTree(expressionTree);
            
            
            free_Tree(expressionTree);
            free_Tree(tree);
        }
    }
    
    
    //free table and grammar
    for (int i = 0; i < grammar_size; i++){
        free(table[i]);
    }
    free(table);
    
    for (int i = 0; i < grammar_size; i++){
        Production_free(grammar[i]);
    }
    free(grammar);
}
