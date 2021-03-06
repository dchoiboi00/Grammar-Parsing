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
    
    //Create productions
    Production E = new_Production("<E>");
    Production_add_to_body(E, "<C>", 1);
    Production_add_to_body(E, "<ET>", 1);
    
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
    
    
    //Read input and print results. Ends on end-of-file in standard input
    while (true){
        printf("\nEnter a regular expression, max 20 characters. Press \"Ctrl + D\" to quit: ");
        scanf("%20s", input);   //take input
        
        if (feof(stdin)){
            printf("\n\nQuit program\n\n");
            break;
        }
        
        /*
         * Part 1: Recursive-Descent Parser
         */
        bool valid = recursive_desc_parser(input);
        
        /*
         * Part 2: Table-Driven Parser   AND
         * Part 3: Build an expression tree, and print in prefix notation
         */
        if (valid) {
            Tree tree = table_driven_parser(input, table, grammar, grammar_size);
            printf("\nPart 2: Table-driven parser\nInputed expression: %s\n", input);
            
            //if the tree is either NULL or if E() ended before the end of the string, print ERROR
            if (tree == NULL){
                printf("ERROR: Invalid expression\n");
            } else {  //otherwise, print our tree
                print_Tree(tree);
                
                LinkedList stack = new_LinkedList();
                createStack(tree, stack);
                //LinkedList_print_string_list(stack);
                
                Tree expressionTree = createExpressionTree(stack);
                //print_Tree(expressionTree);
                
                printf("\nPart 3: Prefix notation of expression tree\n");
                printPrefixExpTree(expressionTree);
                
                printf("\n");
                LinkedList_free(stack, false);
                free_Tree(expressionTree);
                free_Tree(tree);
            }
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
