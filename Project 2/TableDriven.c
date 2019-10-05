//
//  TableDriven.c
//  Project 2
//
//  Created by Daniel Choi on 10/3/19.
//  Copyright © 2019 Daniel Choi. All rights reserved.
//

#include "TableDriven.h"

char *nextInputChar_table;  //Remaining input string

/**
 * Matches c to the current symbol in nextInputChar.
 * If so, consume the symbol and return true. Otherwise, return false.
 */
bool matchTerminal_table(char c) {
    if (*nextInputChar_table == c) {
        nextInputChar_table++;
        return true;
    } else {
        return false;
    }
}

int** create_parsing_table(Production* grammar, int grammar_size){
    int** table = (int**)malloc(sizeof(int*) * grammar_size);
    
    //Our table is 8 x 128, all pre-allocated
    for (int i = 0; i < grammar_size; i++){
        table[i] = (int*)malloc(sizeof(int) * 128);
        for (int j = 0; j < 128; j++){
            table[i][j] = recursive_find_production_identifier(grammar, grammar_size, i, j, 1);
        }
    }
    
    return table;
}

int recursive_find_production_identifier(Production* grammar, int grammar_size, int production, int lookahead, int body_num){
    LinkedList our_body = NULL;  //the body we will be looking at
    int body_index = 0;
    
    LinkedListIterator bodies_iter = LinkedList_iterator(grammar[production]->list_of_bodies);
    while (body_index < body_num && LinkedListIterator_hasNext(bodies_iter)){  //until body_index == body_num
        our_body = LinkedListIterator_next(bodies_iter);
        body_index++;
    }   //notice body_num is always at least 1, so our_body will be initialized. We just need to iterate to the right body, based on body_num
    free(bodies_iter);
    
    if (body_index < body_num){  //if the while loop stopped because the production we wanted to get to did not exist
        return -1;
    }
    
    char* first_token = LinkedList_elementAt(our_body, 0);
    if (is_Production(first_token)){  //if first token is a syntactic category
        for (int i = 0; i < grammar_size; i++) {  //find that category
            if (strcmp(first_token, grammar[i]->head)==0){  //if we found it
                if (recursive_find_production_identifier(grammar, grammar_size, i, lookahead, 1) != -1){  //if the lookahead is eventually matched, this will return true
                    return (100 * production) + body_num;   //the hundredth digit is the production head identifer, and the ones digit stores which body to use in the parse table
                }
            }
        }
        
        return recursive_find_production_identifier(grammar, grammar_size, production, lookahead, body_num+1); //if the first body didn't work, try the next body
    } else { //if the first token was a terminal
        char terminal[2];
        terminal[0] = (char)lookahead;
        terminal[1] = '\0';
        
        if (strcmp(first_token, terminal) == 0 || strlen(first_token) == 0) {  //if the token matches the lookahead, or if the first token was epsilon
            return (100 * production) + body_num;
        } else { //try the next body in the same production
            return recursive_find_production_identifier(grammar, grammar_size, production, lookahead, body_num+1);
        }
    }
    return -1;    //if all fails
}

Tree find_leftmost_leaf(Tree tree){
    if (LinkedList_isEmpty(tree->children) && is_Production(tree->label)){  //base case
        return tree;
    } else {
        LinkedListIterator children_iter = LinkedList_iterator(tree->children);
        while (LinkedListIterator_hasNext(children_iter)){   //go through each child recursively
            Tree child = LinkedListIterator_next(children_iter);
            if (find_leftmost_leaf(child) != NULL){
                free(children_iter);
                return find_leftmost_leaf(child);
            }
        }
        free(children_iter);
    }
    
    return NULL;
}

Tree table_driven_parser(char* input, int** table, Production* grammar, int grammar_size){
    nextInputChar_table = input;  //reset the input tracker
    LinkedList stack = new_LinkedList();  //our stack: we will use _add_at_end() and _pop()
    int	production = 0;
    LinkedList_add_at_end(stack, grammar[production]->head);  //start with start symbol on stack
    Tree tree = new_Tree(grammar[production]->head);   //Start the tree, top-down approach
    
    while (!LinkedList_isEmpty(stack)){  //Until the stack is empty
        char* token = LinkedList_pop(stack);
        
        if (is_Production(token)){  //If we popped a Category <S> from the stack
            
            //update production int
            for (int i = 0; i < grammar_size; i++){
                if (strcmp(token, grammar[i]->head) == 0){
                    production = i;
                }
            }
            
            //use the table to get production
            int next_prod_dest = table[production][(int)nextInputChar_table[0]];  //e.g. 102, 401, 708
            if (next_prod_dest == -1){
//                printf("ERROR (destination is -1): Invalid expression\n");
                return NULL;
            }
            
            production = next_prod_dest / 100;  //hundredth digit refers to index in grammar
            int body_num = next_prod_dest % 100; //ones digit (or mod 100, for <X>) refers to which body
            LinkedList our_body = LinkedList_elementAt(grammar[production]->list_of_bodies, body_num-1);
            
            LinkedListIterator body_iter = LinkedList_iterator(our_body);
            LinkedList temp = new_LinkedList();  //temporary list in order to insert into stack in reverse
            Tree leftmost = find_leftmost_leaf(tree);
//            printf("%s   ", leftmost->label);
            while (LinkedListIterator_hasNext(body_iter)) {
                char* s = LinkedListIterator_next(body_iter);
                if (strlen(s) == 0){  //if it is epsilon
                    Tree child = new_Tree("ε");
                    Tree_add_child(leftmost, child);
                } else {  //if it isn't epsilon
                    LinkedList_add_at_front(temp, s);
                    Tree child = new_Tree(s);
                    Tree_add_child(leftmost, child);
                }
            }
            free(body_iter);
            
            //Insert our body into the stack in reverse order
            while (!LinkedList_isEmpty(temp)){
                char* s = LinkedList_pop(temp);
                LinkedList_add_at_front(stack, s);
            }
            
        } else {   //If we popped a terminal from the stack
            if (!matchTerminal_table(token[0]) && strlen(token) > 0) {  //try to match and consume the terminal, don't do anything on epsilon
//                printf("ERROR (terminal doesn't match): Invalid expression\n");
                return NULL;
            }
        }
    }
    
    if (nextInputChar_table[0] != '\0') {  //if we ended before the end of the string, print ERROR
//        printf("ERROR (ended early): Invalid expression\n");
        return NULL;
    }
    
    return tree;
}
