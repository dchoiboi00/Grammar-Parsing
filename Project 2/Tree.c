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
    Tree_add_child(tree, new_Tree("ε"));
    return tree;
}

Tree new_Tree_one_child(char* label, Tree child1){
    Tree tree = new_Tree(label);
    Tree_add_child(tree, child1);
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

bool isFull(Tree tree){
    LinkedListIterator iter = LinkedList_iterator(tree->children);
    int counter = 0;
    while (LinkedListIterator_hasNext(iter)){
        LinkedListIterator_next(iter);
        counter++;
    }
    free(iter);
    
//    printf("Number of leaves: %d\n", counter);
    if (strcmp(tree->label, "*")==0){
        return counter >= 1;
    } else {
        return counter >= 2;
    }
}

//Free the label, and the children
void free_Tree(Tree tree){
    if (!LinkedList_isEmpty(tree->children)){
        LinkedList_free(tree->children, true);
    } else {
        LinkedList_free(tree->children, false);
    }
    free(tree);
}

//Add child to the end of tree's children linkedlist
void Tree_add_child(Tree tree, Tree child){
    LinkedList_add_at_end(tree->children, child);
}

//print tree with correct indentation
void print_Tree(Tree tree){
    recursive_print_Tree(tree, 0); //start from 0 to get the ball rolling
}

//recursive print tree function: traversal goes parent -> leftChild -> rightChild
void recursive_print_Tree(Tree tree, int indent){
    //print the indentation, equal to indent level
    for (int i = 0; i < indent; i++){
        printf("    ");
    }
    printf("%s\n", tree->label);  //print the parent label
    
    //print children recursively
    LinkedListIterator children_iter = LinkedList_iterator(tree->children);
    while (LinkedListIterator_hasNext(children_iter)){
        Tree child = LinkedListIterator_next(children_iter);
        recursive_print_Tree(child, indent + 1);
    }
    free(children_iter);
}
