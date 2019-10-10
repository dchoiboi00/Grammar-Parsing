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
    if (strcmp(first, ")")==0){
        addParentheses(tempStack, stack);
    } else {
        Tree firstVal = new_Tree(first);
        LinkedList_add_at_front(tempStack, firstVal);
    }
    
    while (!LinkedList_isEmpty(stack)){
        char* next = LinkedList_pop(stack);
//        printf("\nour next char: %s\n", next);
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
//                printf("period at top\n");
                Tree concat = new_Tree_one_child(".", tree);
                LinkedList_add_at_front(tempStack, concat);
            }
        } else if (strcmp(next, "*")==0){
            Tree closure = new_Tree(next);
            Tree tree = LinkedList_pop(tempStack);
            Tree current = tree;
            while (isFull(current)){
//                printf("went down a level\n");
                current = LinkedList_elementAt(current->children, 0);
            }
            
            LinkedList_add_at_front(current->children, closure);
            LinkedList_add_at_front(tempStack, tree);
        } else if (strcmp(next, ")")==0){
            addParentheses(tempStack, stack);
        } else {   //if it is a lowercase letter
            Tree letter = new_Tree(next);
            Tree tree = LinkedList_pop(tempStack);
            Tree current = tree;
            while (isFull(current)){
//                printf("went down a level\n");
                current = LinkedList_elementAt(current->children, 0);
            }
            
            LinkedList_add_at_front(current->children, letter);
            LinkedList_add_at_front(tempStack, tree);
        }
    }
    
    Tree final = LinkedList_pop(tempStack);
    LinkedList_free(tempStack, false);
    return final;
}

void addParentheses(LinkedList tempStack, LinkedList stack){
//    printf("started adding a parentheses\n");
    LinkedList_add_at_front(tempStack, new_Tree(")"));
    
    //initialize the tempStack. Notice this is same code as above until we see a '('
    char* first = LinkedList_pop(stack);
    if (strcmp(first, ")")==0){
        addParentheses(tempStack, stack);
    } else {
        Tree firstVal = new_Tree(first);
        LinkedList_add_at_front(tempStack, firstVal);
    }
    
    while (!LinkedList_isEmpty(stack)){
        char* next = LinkedList_pop(stack);
//        printf("\nour next char: %s\n", next);
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
//                printf("period at top\n");
                Tree concat = new_Tree_one_child(".", tree);
                LinkedList_add_at_front(tempStack, concat);
            }
        } else if (strcmp(next, "*")==0){
            Tree closure = new_Tree(next);
            Tree tree = LinkedList_pop(tempStack);
            Tree current = tree;
            while (isFull(current)){
//                printf("went down a level\n");
                current = LinkedList_elementAt(current->children, 0);
            }
            
            LinkedList_add_at_front(current->children, closure);
            LinkedList_add_at_front(tempStack, tree);
        } else if (strcmp(next, ")")==0){
            addParentheses(tempStack, stack);
        } else if (strcmp(next, "(")==0){      //OUR ENDING CONDITION
            Tree expressionInside = LinkedList_pop(tempStack);
            Tree closeParen = LinkedList_pop(tempStack);
            Tree fullParen = new_Tree_two_children("(", expressionInside, closeParen);
            
//            LinkedList_print_string_list(tempStack);
            
            if (LinkedList_isEmpty(tempStack)){
                LinkedList_add_at_front(tempStack, fullParen);
//                printf("kept the full paren on stack\n");
            } else {  //if there's something on the tempStack
                Tree tree = LinkedList_pop(tempStack);
                if (strcmp(tree->label, ")")==0) {
                    LinkedList_add_at_front(tempStack, tree);   //just put it back on
                    LinkedList_add_at_front(tempStack, fullParen);  //same as if it was empty
                } else {
//                    printf("something else on stack: %s\n", tree->label);
                    
                    Tree current = tree;
                    while (isFull(current)){
                        printf("went down a level\n");
                        current = LinkedList_elementAt(current->children, 0);
                    }
                    
                    LinkedList_add_at_front(current->children, fullParen);
                    LinkedList_add_at_front(tempStack, tree);
                }
            }
            break;  //break the while loop
        } else {   //if it is a lowercase letter
            Tree letter = new_Tree(next);
            Tree tree = LinkedList_pop(tempStack);
            Tree current = tree;
            while (isFull(current)){
                printf("went down a level\n");
                current = LinkedList_elementAt(current->children, 0);
            }
            
            LinkedList_add_at_front(current->children, letter);
            LinkedList_add_at_front(tempStack, tree);
        }
    }
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
        printf(") ");
    }
    
}
