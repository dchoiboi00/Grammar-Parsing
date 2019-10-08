//
//  ExpressionTree.c
//  Project 2
//
//  Created by Daniel Choi on 10/7/19.
//  Copyright © 2019 Daniel Choi. All rights reserved.
//

#include "ExpressionTree.h"
#include "Tree.h"

//leftChild -> parent -> remaining children
void createStack(Tree tree, LinkedList stack){
    LinkedListIterator children_iter = LinkedList_iterator(tree->children);
    
    //left child
    if (LinkedListIterator_hasNext(children_iter)){
        Tree leftChild = LinkedListIterator_next(children_iter);
        createStack(leftChild, stack);
    }
    
    //parent
    if ( !(tree->label[0] == '<') && strcmp(tree->label, "ε")!=0 ){
        LinkedList_add_at_front(stack, tree->label);
    }
    
    //remaining children
    while (LinkedListIterator_hasNext(children_iter)){
        Tree remainingChild = LinkedListIterator_next(children_iter);
        createStack(remainingChild, stack);
    }
    
    free(children_iter);
}

Tree createExpressionTree(LinkedList stack){
    LinkedList tempStack = new_LinkedList();
    
    //initialize the tempStack
    char* first = LinkedList_pop(stack);
    Tree firstVal = new_Tree(first);
    LinkedList_add_at_front(tempStack, firstVal);
    
    while (!LinkedList_isEmpty(stack)){
        char* next = LinkedList_pop(stack);
        if (strcmp(next, "|")==0){
            Tree union_bar = new_Tree_one_child("|", LinkedList_pop(tempStack));
            LinkedList_add_at_front(tempStack, union_bar);
        } else if (strcmp(next, ".")==0){
            Tree tree = LinkedList_pop(tempStack);
            if (strcmp(tree->label, "|")==0){
                Tree child = LinkedList_pop(tree->children);
                LinkedList_add_at_front(tree->children, new_Tree_one_child(".", child));
                LinkedList_add_at_front(tempStack, tree);
            } else {
                printf("ran this\n");
                Tree concat = new_Tree_one_child(".", tree);
                LinkedList_add_at_front(tempStack, concat);
            }
        } else if (strcmp(next, "*")==0){
            
        } else if (strcmp(next, ")")==0){
            
        } else if (strcmp(next, "(")==0){
            
        } else {   //if it is a lowercase letter
            Tree letter = new_Tree(next);
            Tree tree = LinkedList_pop(tempStack);
            if (hasOneChild(tree)){
                printf("had one child on letter\n");
                LinkedList_add_at_front(tree->children, letter);
            }
            
            LinkedList_add_at_front(tempStack, tree);
        }
    }
    
    
    return LinkedList_pop(tempStack);
}

void printPrefixExpTree(Tree tree){
    
    //parent
    if (strcmp(tree->label, "|")==0){
        printf("(UNION ");
    } else if (strcmp(tree->label, ".")==0){
        printf("(CONCAT ");
    } else if (strcmp(tree->label, "*")==0){
        printf("(CLOSURE ");
    } else if (strcmp(tree->label, "(")==0){
        printf("(ATOMIC ");
    } else if (strcmp(tree->label, ")")==0){
        printf(") ");
    } else {   //lowercase letter
        printf("(ATOMIC %s) ", tree->label);
    }
    
    //children
    if (!LinkedList_isEmpty(tree->children)){
        LinkedListIterator children_iter = LinkedList_iterator(tree->children);
        
        //children
        while (LinkedListIterator_hasNext(children_iter)){
            Tree child = LinkedListIterator_next(children_iter);
            printPrefixExpTree(child);
        }
        free(children_iter);
    }
    
    //print ')'
    if ( strcmp(tree->label, "|")==0 || strcmp(tree->label, ".")==0 || strcmp(tree->label, "*")==0){
        printf(")");
    }
    
}
