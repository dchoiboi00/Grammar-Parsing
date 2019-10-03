//
//  Tree.h
//  Project 2
//
//  Created by Daniel Choi on 10/2/19.
//  Copyright © 2019 Daniel Choi. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

typedef struct TreeNode* Tree;
struct TreeNode {
    char *label;   //stores the label as a string
    LinkedList children;
};

extern Tree new_Tree(char *label);   //new instance of tree

extern Tree new_Tree_epsilon_child(char* label);  //instance of tree with child epsilon

extern Tree new_Tree_one_child(char* label, Tree child1);  //one child

extern Tree new_Tree_two_children(char* label, Tree child1, Tree child2); //two children

extern Tree new_Tree_three_children(char* label, Tree child1, Tree child2, Tree child3); //three children

extern void free_Tree(Tree tree);  //free tree

extern void Tree_add_child(Tree tree, Tree child);  //add child to tree's children

extern void print_Tree(Tree tree);    //print the tree with correct indentation
#endif /* Tree_h */
