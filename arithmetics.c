#include "arithmetics.h"

double calculate(Queue* que, double x, int *Status) {
    double result = 0.0;
    QueNode* popped = que->head;
    Stack* stack = stack_init();
    while (popped != NULL && *Status == SUCCESS) {
        Lexeme* lex = popped->lex;
        popped = popped->next;
        if (lex->type == NUMBER) {
            Lexeme* new_lex = (Lexeme*)calloc(1, sizeof(Lexeme));
            new_lex->type = NUMBER;
            if (lex->chr != 'x') {
                new_lex->num = lex->num;
            } else {
                new_lex->num = x;
                if (lex->num < 0) new_lex->num *= -1;
            }
            stack_push(stack, new_lex);
        }
        if (lex->type == FUNCTION) {
            Lexeme* popped_lex = stack_pop(stack);
            if (is_invalid_num(popped_lex, Status) == false) {
                double res_value = calculate_func(popped_lex->num, lex->chr);
                popped_lex->num = res_value;
                stack_push(stack, popped_lex);
            }
        }
        if (lex->type == OPERATOR) {
            Lexeme* popped_lex1 = stack_pop(stack);
            Lexeme* popped_lex2 = stack_pop(stack);
            if (is_invalid_lexemes(popped_lex1, popped_lex2, Status) == false) {
                double res_value = calculate_nums(popped_lex1->num, popped_lex2->num, lex->chr);
                free(popped_lex1);
                free(popped_lex2);
                Lexeme* new_lex = (Lexeme*)calloc(1, sizeof(Lexeme));
                new_lex->num = res_value;
                new_lex->type = NUMBER;
                stack_push(stack, new_lex);
            }
        }
    }
    Lexeme* result_lex = stack_pop(stack);
    if (is_invalid_num(result_lex, Status) == false) {
        result = result_lex->num;
        free(result_lex);
    } else {
        printf("\n!ERR:result is NOT a num\n");
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

bool is_invalid_num(Lexeme *num, int *Status) {
    bool is_invalid = false;
    if (num == NULL) {
        is_invalid = true;
    } else if (num->type != NUMBER) {
        is_invalid = true;
    }
    *Status = is_invalid ? FAIL : SUCCESS;
    return is_invalid;
}

bool is_invalid_lexemes(Lexeme *num1, Lexeme *num2, int *Status) {
    bool is_invalid = false;
    if (is_invalid_num(num1, Status) || is_invalid_num(num2, Status)) {
        is_invalid = true;
    }
    is_invalid ? printf(WRONG_EXP) : 0;
    return is_invalid;
}

bool is_trigonometric(char op) {
    bool is_trig = false;
    if (op == COS || op == SIN || op == TAN) {
            is_trig = true;
    }
    return is_trig;
}