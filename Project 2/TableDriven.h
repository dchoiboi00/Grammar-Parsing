//
//  TableDriven.h
//  Project 2
//
//  Created by Daniel Choi on 10/3/19.
//  Copyright © 2019 Daniel Choi. All rights reserved.
//

#ifndef TableDriven_h
#define TableDriven_h

#include <stdio.h>
#include "Tree.h"
#include "Production.h"
#include "RecursiveDescent.h"

extern bool matchTerminal_table(char c);

/*
 * Creates and returns the parsing table. Syntactic Category X Lookahead -> Production
 */
extern int** create_parsing_table(Production* grammar, int grammar_size);

/*
 * Recursively finds the production to put into the parsing table, given the Category and Lookahead
 */
extern int recursive_find_production_identifier(Production* grammar, int grammar_size, int production, int lookahead, int body_num);

extern Tree find_leftmost_leaf(Tree tree);  //returns the leftmost leaf that has a non-terminal as label

extern Tree table_driven_parser(char* input, int** table, Production* grammar, int grammar_size);

#endif /* TableDriven_h */
