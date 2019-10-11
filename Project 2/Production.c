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
    LinkedListIterator bodies_iter = LinkedList_iterator(production->list_of_bodies);
    while (LinkedListIterator_hasNext(bodies_iter)){  //iterates over the different bodies
        LinkedList body = LinkedListIterator_next(bodies_iter);  //free the bodies
        LinkedList_free(body, false);
    }
    free(bodies_iter);
    
    LinkedList_free(production->list_of_bodies, false);    //free the list_of_bodies
    
    free(production);
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
