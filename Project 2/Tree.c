//
//  Tree.c
//  Project 2
//
//  Created by Daniel Choi on 10/2/19.
//  Copyright © 2019 Daniel Choi. All rights reserved.
//

#include "Tree.h"

Tree new_Tree(char* label) {
    Tree tree = (Tree)malloc(sizeof(struct TreeNode));
    
    tree->label = label;
    tree->children = new_LinkedList();
    return tree;
}

Tree new_Tree_epsilon_child(char* label) {
    Tree tree = new_Tree(label);
    Tree_add_child(tree, new_Tree("eps"));
    return tree;
}

Tree new_Tree_two_children(char* label, Tree child1, Tree child2){
    Tree tree = new_Tree(label);
    Tree_add_child(tree, child1);
    Tree_add_child(tree, child2);
    return tree;
}

Tree new_Tree_three_children(char* label, Tree child1, Tree child2, Tree child3){
    Tree tree = new_Tree(label);
    Tree_add_child(tree, child1);
    Tree_add_child(tree, child2);
    Tree_add_child(tree, child3);
    return tree;
}

//Free the label, and the children
void free_Tree(Tree tree){
    free(tree->label);
    LinkedList_free(tree->children, true);
}

//Add child to the end of tree's children linkedlist
void Tree_add_child(Tree tree, Tree child){
    LinkedList_add_at_end(tree->children, child);
}

void print_Tree(Tree tree){
    
}
