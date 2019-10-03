//
//  RecursiveDescent.c
//  Project 2
//
//  Created by Daniel Choi on 10/2/19.
//  Copyright © 2019 Daniel Choi. All rights reserved.
//

#include "RecursiveDescent.h"

char *nextInputChar;  //Remaining input string

/**
 * Matches c to the current symbol in nextInputChar.
 * If so, consume the symbol and return true. Otherwise, return false.
 */
bool matchTerminal(char c) {
    if (*nextInputChar == c) {
        nextInputChar++;
        return true;
    } else {
        return false;
    }
}

/**
 * Return true if the next input char matches c, otherwise return false
 * Does not consume the symbol, it just checks.
 */
bool lookahead(char c){
    return *nextInputChar ==c;
}

/**
 * Production: <E> -> <C><ET>
 */
Tree parseE() {
    Tree C = parseC();
    if (C == NULL){
        return NULL;
    }
    
    Tree ET = parseET();
    if (ET == NULL){
        return NULL;
    }
    
    //return resulting tree
    return new_Tree_two_children("<E>", C, ET);
}


/**
 * Production: <ET> -> |<E>  |   eps
 */
Tree parseET() {
    if (!lookahead('|')){
        return new_Tree_epsilon_child("<ET>");
    } else {  //if the lookahead IS "|"
        if (!matchTerminal('|')){
            return NULL;
        }
        Tree E = parseE();
        if (E == NULL){
            return NULL;
        }
        
        //return resulting tree
        return new_Tree_two_children("<ET>", new_Tree("|"), E);
    }
}


/**
 * Production: <C> -> <S><CT>
 */
Tree parseC() {
    Tree S = parseS();
    if (S == NULL){
        return NULL;
    }
    
    Tree CT = parseCT();
    if (CT == NULL){
        return NULL;
    }
    
    //return resulting tree
    return new_Tree_two_children("<C>", S, CT);
}

/**
 * Production: <CT> -> .<C>  |   eps
 */
Tree parseCT() {
    if (!lookahead('.')){
        return new_Tree_epsilon_child("<CT>");
    } else {  //if the lookahead IS "."
        if (!matchTerminal('.')){
            return NULL;
        }
        Tree C = parseC();
        if (C == NULL){
            return NULL;
        }
        
        //return resulting tree
        return new_Tree_two_children("<CT>", new_Tree("."), C);
    }
}

/**
 * Production: <S> -> <A><ST>
 */
Tree parseS() {
    Tree A = parseA();
    if (A == NULL){
        return NULL;
    }
    
    Tree ST = parseST();
    if (ST == NULL){
        return NULL;
    }
    
    //return resulting tree
    return new_Tree_two_children("<S>", A, ST);
}

/**
 * Production: <ST> -> *<ST>  |   eps
 */
Tree parseST() {
    if (!lookahead('*')){
        return new_Tree_epsilon_child("<ST>");
    } else {  //if the lookahead IS "*"
        if (!matchTerminal('*')){
            return NULL;
        }
        Tree ST = parseST();
        if (ST == NULL){
            return NULL;
        }
        
        //return resulting tree
        return new_Tree_two_children("<ST>", new_Tree("*"), ST);
    }
}

/**
 * Production: <A> -> (<E>)  |   <X>
 */
Tree parseA() {
    if (lookahead('(')){
        if (!matchTerminal('(')){
            return NULL;
        }
        Tree E = parseE();
        if (E == NULL){
            return NULL;
        }
        if (!matchTerminal(')')){
            return NULL;
        }
        
        //return resulting tree
        return new_Tree_three_children("<A>", new_Tree("("), E, new_Tree(")"));
    } else {  //if the lookahead is NOT (
        Tree X = parseX();
        if (X == NULL){
            return NULL;
        }
        
        //return resulting tree
        return new_Tree_one_child("<A>", X);
    }
}

/**
 * Production: <X> -> a | b | ... | z
 */
Tree parseX() {
    char alphabet[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};
    
    for (int i = 0; i < 26; i++){  //for each letter in the lowercase alphabet
        if (lookahead(alphabet[i])){
            if (!matchTerminal(alphabet[i])){  //if we find it in lookahead, match and consume it
                return NULL;
            }
            char str[2];
            str[0] = alphabet[i];
            str[1] = '\0';
            printf("Our <X> has child: %s\n", str);
            return new_Tree_one_child("<X>", new_Tree(str));
        }
    }
    
    //if we couldn't match any of the letters in the alphabet
    return NULL;
}

/**
 * Part 1: Recursive-Descent Parser starter function
 */
void recursive_desc_parser(char *input) {
    printf("Inputed expression: %s\n", input);
    nextInputChar = input;   //initialize the input tracker
    
    Tree tree = parseE();
    
    //if the tree is either NULL or if E() ended before the end of the string, print ERROR
    if (tree == NULL || !lookahead('\0')){
        printf("ERROR: Invalid expression\n");
    } else {  //otherwise, print our tree
        print_Tree(tree);
    }
}
