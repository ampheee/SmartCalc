#include "arithmetics.h"

double calculate(Queue* que, double x) {
    double result = 0.0;
    QueNode* popped = que->head;
    Stack* stack = stack_init();
    while (popped != NULL) {
        Lexeme* lex = popped->lex;
        popped = popped->next;
        // if current lexeme is number
        if (lex->type == NUMBER) {
            Lexeme* lexnum = (Lexeme*)calloc(1, sizeof(lex));
            lexnum->type = NUMBER;
            if (lex->chr != 'x') {
                lexnum->num = lex->num;
            } else {
                lexnum->num = x;
                if (lex->num < 0) lexnum->num *= -1;
            }
            stack_push(stack, lexnum);
        }
        // if is function
        if (lex->type == FUNCTION) {
            Lexeme* lexnum = stack_pop(stack);
            if (lexnum->type != NUMBER)
                printf("\n!ERR:stack->num is NOT a num\n");
            double res_value = calculate_func(to_radians(lexnum->num), lex->chr);
            lexnum->num = res_value;
            stack_push(stack, lexnum);
        }
        // if is operator
        if (lex->type == OPERATOR) {
            Lexeme* num1 = stack_pop(stack);
            Lexeme* num2 = stack_pop(stack);
            if (num1->type != NUMBER) printf("\n!ERR:num1 is NOT a num");
            if (num2->type != NUMBER) printf("\n!ERR:num2 is NOT a num");
            double res_value = calculate_nums(num1->num, num2->num, lex->chr);
            free(num1);
            free(num2);
            Lexeme* lexnum = (Lexeme*)calloc(1, sizeof(lex));
            lexnum->num = res_value;
            lexnum->type = NUMBER;
            stack_push(stack, lexnum);
        }
    }
    Lexeme* stackResult = stack_pop(stack);
    if (stackResult->type != NUMBER) printf("\n!ERR:result is NOT a num\n");
    result = stackResult->num;
    free(stackResult);
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
    double retval;
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
            retval = acos(value);
            break;
        case ASIN:
            retval = asin(value);
            break;
        case ATAN:
            retval = atan(value);
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