#ifndef _SMARTCALC_ARITHMETICS_H_
#define _SMARTCALC_ARITHMETICS_H_

#include "calculator.h"

#define MAP_SIZE 6

typedef struct Node {
    char L;
    LStack *next;
} LStack;

struct Priority {
    struct key key;
    struct Value value;
};

struct Key {
    struct point p1;
    struct point p2;
    int i;
    int j;
}


//todo: реализовать стек
//todo - в постфиксную запись
//todo - в обратную польскую нотацию
//todo - подсчет и вывод результата/ошибки
//todo - построение и привязка графиков
//todo - кредитные калькуляторы.
#endif //_SMARTCALC_ARITHMETICS_H_
