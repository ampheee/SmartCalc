#ifndef _SMARTCALC_ARITHMETICS_H_
#define _SMARTCALC_ARITHMETICS_H_

#include "calculator.h"

typedef struct LStack {
    char L;
    LStack *next;
} LStack;

struct Priority {
    struct  key;
    struct Value value;
};

int popL();
int backL();
void pushL();
void clearL();


#endif //_SMARTCALC_ARITHMETICS_H_
