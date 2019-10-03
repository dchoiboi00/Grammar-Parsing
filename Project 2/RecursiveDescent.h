//
//  RecursiveDescent.h
//  Project 2
//
//  Created by Daniel Choi on 10/2/19.
//  Copyright © 2019 Daniel Choi. All rights reserved.
//

#ifndef RecursiveDescent_h
#define RecursiveDescent_h

#include <stdio.h>
#include "Tree.h"

extern bool matchTerminal(char c);

extern bool lookahead(char c);

extern Tree parseE(void);

extern Tree parseET(void);

extern Tree parseC(void);

extern Tree parseCT(void);

extern Tree parseS(void);

extern Tree parseST(void);

extern Tree parseA(void);

extern Tree parseX(void);

#endif /* RecursiveDescent_h */
