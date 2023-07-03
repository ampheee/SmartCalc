#ifndef _SMARTCALC_ARITHMETICS_H_
#define _SMARTCALC_ARITHMETICS_H_

#include "calculator.h"

#define MAP_SIZE

typedef struct LStack {
    char L;
    LStack *next;
} LStack;

struct Priority {
    struct  key key;
    struct Value value;
};

struct Key {
    struct point p1;
    struct point p2;
    int i;
    int j;
};



int popL();
int backL();
void pushL();
void clearL();


#endif //_SMARTCALC_ARITHMETICS_H_
