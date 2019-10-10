//
//  ExpressionTree.h
//  Project 2
//
//  Created by Daniel Choi on 10/7/19.
//  Copyright © 2019 Daniel Choi. All rights reserved.
//

#ifndef ExpressionTree_h
#define ExpressionTree_h

#include <stdio.h>
#include "TableDriven.h"

/*
 * Recursively creates a stack storing the inorder traversal of a parse tree.
 */
extern void createStack(Tree tree, LinkedList stack);

/*
 * Creates the expression tree from a parse tree's inorder stack
 */
extern Tree createExpressionTree(LinkedList stack);

/*
 * Adds a set of parentheses to the expression tree
 */
extern void addParentheses(LinkedList tempStack, LinkedList stack);

/*
 * Prints an expression tree in prefix notation. Uses preorder traversal
 */
extern void printPrefixExpTree(Tree tree);

#endif /* ExpressionTree_h */
