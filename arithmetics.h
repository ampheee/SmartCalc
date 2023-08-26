#ifndef SRC_CALC_H_
#define SRC_CALC_H_

#include "stack.h"
#include "queue.h"
#include <math.h>
#include <stdio.h>

#define MODE 'm'

#define COS 'c'
#define SIN 's'
#define TAN 't'
#define ACOS 'C'
#define ASIN 'S'
#define ATAN 'T'
#define SQRT 'q'
#define LN 'l'
#define LOG 'L'

double calculate(Queue* exp, double x);
double calculate_nums(double num1, double num2, char op);
double calculate_func(double value, char op);
double to_radians(double x);

#endif /* SRC_CALC_H_ */