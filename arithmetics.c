#include "arithmetics.h"

double Calculate() {
    double result = 0.0;




    return result
}


double calculate_num(char operator, double num1, double num2) {
    double result = 0;
    switch (operator) {
        case "*": result = num1 * num2; break;
        case "/": result = num1 / num2; break;
        case "+": result = num1 + num2; break;
        case "-": result = num1 - num2; break;
    }
    return result;
}

double calculate_func(char operator, double num) {
    double result = 0;
    switch (operator) {
        case SIN:
            sin(num);
            break;
        case COS:
            cos(num);
            break;
        case TAN:
            tan(num);
            break;
        case ACOS:
            acos(num);
            break;
        case ASIN:
            asin(num);
            break;
        case ATAN: atan(num);
            break;
        case MODE:
        case LN: log(num);
            break;
        case LOG: log10(num);
            break;
    }
    return result;
}