//
//  Production.h
//  Project 2
//
//  Created by Daniel Choi on 10/3/19.
//  Copyright © 2019 Daniel Choi. All rights reserved.
//

#ifndef Production_h
#define Production_h

#include <stdio.h>
#include "Tree.h"

typedef struct ProductionNode* Production;

struct ProductionNode {
    char* head;   //stores the string of left hand side syntactic category: e.g. <E>
    LinkedList list_of_bodies;    //stores a list of LinkedLists, since one head can have several bodies: e.g. <X> -> a | b | ... | z
};

extern Production new_Production(char* head);    //return new instance of production with specified head

extern void Production_free(Production production);   //free a production

extern void Production_add_to_body(Production production, char* name, int body_num); //add a terminal/non-terminal to body with body index of body_num. e.g. adding "b" to <X> would have a body_num of 2

extern bool is_Production(char* string);  //returns whether string is enclosed with '<   >', indicating it is a production

extern void print_Production(Production production);

#endif /* Production_h */
