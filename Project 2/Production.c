//
//  Production.c
//  Project 2
//
//  Created by Daniel Choi on 10/3/19.
//  Copyright © 2019 Daniel Choi. All rights reserved.
//

#include "Production.h"

Production new_Production(char* head){
    Production this = (Production)malloc(sizeof(struct ProductionNode));
    
    this->head = head;
    this->list_of_bodies = new_LinkedList();
    return this;
}

void Production_free(Production production){
    
}

void Production_add_to_body(Production production, char* name, int body_num){
    LinkedListIterator list_of_bodies_iter = LinkedList_iterator(production->list_of_bodies);
    LinkedList our_body = NULL;    //our target body that we want to add to
    
    //cycle through until we get to our body that we want to use
    for (int i = 0; i < body_num; i++){
        if (LinkedListIterator_hasNext(list_of_bodies_iter)){
            our_body = LinkedListIterator_next(list_of_bodies_iter);  //if the production already exists, move forward
        } else {   //create a new body if it doesn't exist
            LinkedListIterator_next(list_of_bodies_iter);
            our_body = new_LinkedList();
            LinkedList_add_at_end(production->list_of_bodies, our_body);
        }
    }
    free(list_of_bodies_iter);
    
    LinkedList_add_at_end(our_body, name);
}

bool is_Production(char* string){
    return string[0] == '<' && string[strlen(string) - 1] == '>';  //checks for < and > at the beginning and end
}

void print_Production(Production production)    //Prints a syntactic category's productions
{
    LinkedListIterator iterator = LinkedList_iterator(production->list_of_bodies); //Iterates over production body
    while (LinkedListIterator_hasNext(iterator))
    {
        printf("%s ->", production->head);   //Prints syntactic category name
        
        LinkedListIterator body_iterator = LinkedList_iterator(LinkedListIterator_next(iterator));  //Iterates over sub-production
        while (LinkedListIterator_hasNext(body_iterator))
        {
            char* s = LinkedListIterator_next(body_iterator);
            
            if (strlen(s) == 0) //Prints epsilon if it is empty
            {
                s = "ε";
            }
            
            printf(" %s", s);   //Prints body otherwise
        }
        
        printf("\n");   //Prints a new line with each subproduction
        free(body_iterator);
    }
    free(iterator);
}
