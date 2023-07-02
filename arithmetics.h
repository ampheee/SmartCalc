//
// Created by ampheee on 6/28/23.
//

#ifndef SMARTCALC_ARITHMETICS_H
#define SMARTCALC_ARITHMETICS_H


typedef struct LStack {
    char L;
    LStack *next;
} LStack;

int popL();
int backL();
void pushL();
void clearL();


#endif //SMARTCALC_ARITHMETICS_H
