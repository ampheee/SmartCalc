#ifndef SMARTCALC_ARITHMETICS_H_
#define SMARTCALC_ARITHMETICS_H_

#include "calculator.h"

#define SUCCESS 1
#define FAIL 0
#define ERROR bool

typedef struct Token {
    char spec;
    unsigned int width;
} Token;

typedef struct Node {
    char L;
    struct Node *next;
} Node;

typedef struct Stack {
    unsigned int size;
    Node *tail;
} Stack;

ERROR parse_num_string(unsigned char **result, char **eval);


//todo: реализовать стек
//todo - в постфиксную запись
//todo - в обратную польскую нотацию
//todo - подсчет и вывод результата/ошибки
//todo - построение и привязка графиков
//todo - кредитные калькуляторы.
#endif //SMARTCALC_ARITHMETICS_H_
