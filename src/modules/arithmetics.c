#include "arithmetics.h"

double calculate(Queue* que, int *Status) {
    double result = 0.0;
    QueNode* popped = que->head;
    Stack* stack = stack_init();
    while (popped != NULL && *Status == SUCCESS) {
        Lexeme* lex = popped->lex;
        popped = popped->next;
        if (lex->type == NUMBER) {
            Lexeme* new_lex = (Lexeme*)calloc(1, sizeof(Lexeme));
            new_lex->type = NUMBER;
            new_lex->num = lex->num;
            stack_push(stack, new_lex);
        }
        if (lex->type == FUNCTION) {
            Lexeme* popped_lex = stack_pop(stack);
            if (is_invalid_num(popped_lex) == false) {
                popped_lex->num = calculate_func(popped_lex->num, lex->chr);
                stack_push(stack, popped_lex);
            } else {
                *Status = FAIL;
            }
        }
        if (lex->type == OPERATOR) {
            Lexeme* lex1 = stack_pop(stack);
            Lexeme* lex2 = stack_pop(stack);
            if (lex1 || lex2) {
                Lexeme* new_lex = (Lexeme*)calloc(1, sizeof(Lexeme));
            if (!is_invalid_num(lex1) && is_invalid_num(lex2) &&
                (lex->chr == '-' || lex->chr == '+')) {
                new_lex->num =calculate_nums(lex1->num, 0, lex->chr);
                free(lex1);
            } else if (is_invalid_num(lex1) && !is_invalid_num(lex2) &&
                (lex->chr == '-' || lex->chr == '+')) {
                new_lex->num = calculate_nums(lex2->num, 0, lex->chr);
                free(lex2);
            } else if (is_invalid_lexemes(lex1, lex2, Status) == false) {
                new_lex->num = calculate_nums(lex1->num, lex2->num, lex->chr);
                free(lex1);
                free(lex2);
                }
            new_lex->type = NUMBER;
            stack_push(stack, new_lex);
            } else {
                *Status = FAIL;
            }
        }
    }
    Lexeme* result_lex = stack_pop(stack);
    if (is_invalid_num(result_lex) == false) {
        result = result_lex->num;
        free(result_lex);
    } else {
        printf("\n!ERR:result is NOT a num\n %p", result_lex);
    }
    if (stack->size > 0) {
        printf(WRONG_EXP);
        *Status = FAIL;
    }
    stack_free(stack);
    return result;
}

double calculate_nums(double num1, double num2, char op) {
    double res = 0;
    switch (op) {
        case '+':
            res = num2 + num1;
            break;
        case '-':
            res = num2 - num1;
            break;
        case '*':
            res = num2 * num1;
            break;

        case '/':
            if (fabs(num1) > __FLT_EPSILON__)
                res = num2 / num1;
            else
                res = NAN;
            break;
        case '^':
            res = pow(num2, num1);
            break;
        case MOD:
            res = fmod(num2, num1);
            break;
        default:
            printf("\n!ERR:UNKNOWN OPERATOR '%c'\n", op);
            break;
    }
    return res;
}

double calculate_func(double value, char op) {
    double retval = 0;
    if (is_trigonometric(op)) {
        value = to_radians(value);
    }
    switch (op) {
        case COS:
            retval = cos(value);
            break;
        case SIN:
            retval = sin(value);
            break;
        case TAN:
            retval = tan(value);
            break;
        case ACOS:
            retval = to_degrees(acos(value));
            break;
        case ASIN:
            retval = to_degrees(asin(value));
            break;
        case ATAN:
            retval = to_degrees(atan(value));
            break;
        case SQRT:
            retval = sqrt(value);
            break;
        case LN:
            retval = log(value);
            break;
        case LOG:
            retval = log10(value);
            break;
        default:
            printf("\n!ERR:UNKNOWN FUNCTION '%c'\n", op);
            break;
    }
    return retval;
}

double to_radians(double x) {
    double radians = x * ( M_PI / 180);
    return radians;
}

double to_degrees(double x) {
    double degrees = x * (180 / M_PI);
    return degrees;
}

bool is_invalid_num(Lexeme *num) {
    bool is_invalid = false;
    if (num == NULL) {
        is_invalid = true;
    } else if (num->type != NUMBER) {
        is_invalid = true;
    }
    return is_invalid;
}

bool is_invalid_lexemes(Lexeme *num1, Lexeme *num2, int *Status) {
    bool is_invalid = false;
    if (is_invalid_num(num1) && is_invalid_num(num2)) {
        *Status = FAIL;
        is_invalid = true;
    }
    return is_invalid;
}

bool is_trigonometric(char op) {
    bool is_trig = false;
    if (op == COS || op == SIN || op == TAN) {
            is_trig = true;
    }
    return is_trig;
}