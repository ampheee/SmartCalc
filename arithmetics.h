#ifndef SRC_CALC_H_
#define SRC_CALC_H_

#include <math.h>

# define M_PI		3.14159265358979323846

#include "stack.h"
#include "queue.h"
#include <stdio.h>
#include "parse.h"

#define WRONG_EXP "Wrong Expression\n"

#define MOD 'm'
#define COS 'c'
#define SIN 's'
#define TAN 't'
#define ACOS 'C'
#define ASIN 'S'
#define ATAN 'T'
#define SQRT 'q'
#define LN 'l'
#define LOG 'L'

double calculate(Queue* exp, double x, int *Status);
double calculate_nums(double num1, double num2, char op);
double calculate_func(double value, char op);
double to_radians(double x);
double to_degrees(double x);
bool is_invalid_num(Lexeme *num, int *Status);
bool is_invalid_lexemes(Lexeme *num1, Lexeme *num2, int *Status);
bool is_trigonometric(char op);

#endif /* SRC_CALC_H_ */