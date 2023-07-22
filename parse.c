#include "parse.h"

bool isBasedDigit(char c, int b) {
    bool res = false;
    if (b > 10) {
        res = (c >= '0' && c <= '9') || (c >= 'a' && c < 'a' + b - 10) ||
              (c >= 'A' && c < 'A' + b - 10);
    } else {
        res = c >= '0' && c < '0' + b;
    }
    return res;
}

bool isExp(char **sptr, int *e) {
    int result = FAIL;
    if (**sptr == 'e' || **sptr == 'E') {
        bool isNegative = 0;
        (*sptr)++;
        if (**sptr && **sptr == '+') {
            (*sptr)++;
        } else if (**sptr && **sptr == '-') {
            isNegative = true;
            (*sptr)++;
        }
        while (**sptr && isBasedDigit(**sptr, 10)) {
            *e = *e * 10 + (**sptr - '0');
            (*sptr)++;
        }
        if (isNegative) {
            *e *= -1;
        }
        result = SUCCESS;
    }
    return result;
}

double s21_atof(char **sptr, size_t *numsCount) {
    long double res = 0.0;
    bool dot = false;
    if (**sptr != '.' && isBasedDigit(**sptr, 10)) {
        res += **sptr - '0';
        (*sptr)++;
        *numsCount = *numsCount + 1;
    }
    for (; **sptr && (isBasedDigit(**sptr, 10) || **sptr == '.');
           (*sptr)++) {
        if (**sptr == '.') {
            dot = true;
            break;
        } else {
            *numsCount = *numsCount + 1;
            res = res * 10 + (**sptr - '0');
        }
    }
    int e = 0, eDot = 0;
    if (dot) {
        (*sptr)++;
        while (**sptr && isBasedDigit(**sptr, 10)) {
            *numsCount = *numsCount + 1;
            res = res * 10 + (**sptr - '0');
            eDot--;
            (*sptr)++;
        }
    }
    isExp(sptr, &e);
    e = e + eDot;
    if (e > 0) {
        while (e != 0) {
            res *= 10;
            e--;
        }
    } else if (e < 0) {
        while (e != 0) {
            res /= 10;
            e++;
        }
    }
    return res;
}

int parse_num(char **str, double *result) {
    bool Status = FAIL;
    size_t nums_count = 0;
    *result = s21_atof(str, &nums_count);
    if (nums_count != 0) {
        Status = SUCCESS;
    }
    return Status;
}

int parse_func(char **str, unsigned char *result) {
    int Status = FAIL;
     if (strstr(*str, "cos") == *str || strstr(*str, "sin") == *str ||
        strstr(*str, "tan") == *str || strstr(*str, "ln") == *str) {
        (*str) += 3;
        *result = (*str)[0];
        if (*result == 'l') (*str)--;
        Status = SUCCESS;
    }
    if ((Status == FAIL) &&
        (strstr(*str, "acos") == *str || strstr(*str, "asin") == *str ||
         strstr(*str, "atan") == *str || strstr(*str, "sqrt") == *str)) {
        (*str) += 4;
        *result = (*str)[1];
        if ((*str)[1] != 'q') *result -= 32;
        Status = SUCCESS;
    }
    if ((Status == FAIL) && strstr(*str, "log") == *str) {
        (*str) += 3;
        *result = 'L';
        Status = SUCCESS;
    }
    return Status;
}

int parse_operator(char **str, unsigned char *result) {
    int Status = SUCCESS;
    if (strstr(*str, "+") == *str) {
        *result = '+';
    } else if (strstr(*str, "-") == *str) {
        *result = '-';
    } else if (strstr(*str, "/") == *str) {
        *result = '/';
    } else if (strstr(*str, "*") == *str) {
        *result = '*';
    } else if (strstr(*str, "^") == *str) {
        *result = '^';
    } else if (strstr(*str, "mod") == *str) {
        *result = 'm';
    } else {
        Status = FAIL;
    }
    if (Status == SUCCESS) {
        (*str)++;
        if (*result == 'm') {
            (*str) += 2;
        }
    }
    return Status;
}

int parse_bracket(char **str, unsigned char *result) {
    int Status = FAIL;
    if (strstr(*str, "(") == *str || strstr(*str, ")") == *str) {
        *result = **str;
        Status = SUCCESS;
        (*str)++;
    }
    return Status;
}

void remove_spaces(char **str) {
    while (**str && (**str == ' ' || **str == '\t' || **str == '\n')) {
        (*str)++;
    }
}

int get_priority(char operator) {
    int result = -1;
    if (operator == '+' || operator == '-') {
        result = 1;
    } else if (operator == '*' || operator == '/' || 
        operator == 'm' || strchr("cstCSTqlL", operator) != NULL) {
        result = 2;
    } else if (operator == '^') {
        result = 3;
    }
}

int is_op2_priority_higher_or_equal(char op1, char op2) {
    int Status = FAIL;
    int priority_op1 = get_priority(op1);
    int priority_op2 = get_priority(op2);
    if (priority_op1 > 0 && priority_op2 > 0 && 
        priority_op2 >= priority_op1) {
            Status = priority_op2;
        }
    return Status;
}

int str_to_polish(char *str, Queue **res) {
    Stack *stack = stack_init();
    *res = queue_init();
    int Status = SUCCESS;
    size_t len = strlen(str);
    while (*str && Status == SUCCESS) {
        remove_spaces(&str);
        Lexeme *lex = (Lexeme *) calloc (1, sizeof(Lexeme));
        if (isBasedDigit(*str, 10)) {
            double result = 1;
            Status = parse_num(&str, &result);
            lex->type = NUMBER;
            lex->num = result;
            queue_push(*res, lex);
;        } else if (parse_operator(&str, &lex->chr) == SUCCESS) {
            lex->type = OPERATOR;
        } else if (parse_func(&str, &lex->chr) == SUCCESS) {
            lex->type = FUNCTION;
        } else if (parse_bracket(&str, &lex->chr) == SUCCESS) {
            lex->type = BRACKET;
        } else {
            Status = FAIL;
        }
        // queue_push(*res, lex);
        if (Status == SUCCESS && lex->type != NUMBER) {
            while (stack->size > 0) {
                Lexeme *seeked = stack_seek(stack);
                if (is_op2_priority_higher_or_equal(seeked->chr, lex->chr) == FAIL) {
                    stack_push(stack, lex);
                    break;
                }
                Lexeme *popped = stack_pop(stack);
                queue_push(*res, popped);
                free(popped);
            }
            if (stack->size == 0) {
                stack_push(stack, lex);
            }
        }
        if (Status == FAIL) free(lex);
    }
    while (stack->size != 0) {
        Lexeme *popped = stack_pop(stack);
        queue_push(*res, popped);
    }
    print_stack(stack);
    free(stack);
    return Status;
}