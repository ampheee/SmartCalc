#ifndef SMARTCALC_ARITHMETICS_H_
#define SMARTCALC_ARITHMETICS_H_

#include "stack.h"
#include "queue.h"
#include "debug.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define SUCCESS 1
#define FAIL (-1)

typedef bool ERROR;

#define s21_INFINITY 1.0 / 0.0
#define s21_NEG_INFINITY -1.0 / 0.0
#define s21_NAN 0.0 / 0.0
int parse_num(char **str, double *res);
int parse_func(char **str, unsigned char *result);
int parse_bracket(char **str, unsigned char *result);
int parse_operator(char **str, unsigned char *result);
int check_priority(char op1, char op2);
void remove_spaces(char **str);
bool isBasedDigit(char c, int b);
bool isExp(char **sptr, int *e);
double s21_atof(char **sptr, size_t *numsCount);
int str_to_polish(char *str, Queue **res);

#endif //SMARTCALC_ARITHMETICS_H_
