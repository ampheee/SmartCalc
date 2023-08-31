#include "parse.h"

bool is_based_digit(char c, int b) {
    bool res = false;
    if (b > 10) {
        res = (c >= '0' && c <= '9') || (c >= 'a' && c < 'a' + b - 10) ||
              (c >= 'A' && c < 'A' + b - 10);
    } else {
        res = c >= '0' && c < '0' + b;
    }
    return res;
}

bool is_exp(char **sptr, int *e) {
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
        while (**sptr && is_based_digit(**sptr, 10)) {
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

double parse_to_float(char **sptr, size_t *numsCount) {
    long double res = 0.0;
    bool dot = false;
    if (**sptr != '.' && is_based_digit(**sptr, 10)) {
        res += **sptr - '0';
        (*sptr)++;
        *numsCount = *numsCount + 1;
    }
    for (; **sptr && (is_based_digit(**sptr, 10) || **sptr == '.');
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
        while (**sptr && is_based_digit(**sptr, 10)) {
            *numsCount = *numsCount + 1;
            res = res * 10 + (**sptr - '0');
            eDot--;
            (*sptr)++;
        }
    }
    is_exp(sptr, &e);
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
    int Status = FAIL;
    if (is_based_digit(**str, 10) == true) {
        size_t nums_count = 0;
        *result = parse_to_float(str, &nums_count);
        if (nums_count != 0) {
            Status = SUCCESS;
        }
    }
    return Status;
}

int parse_func(char **str, unsigned char *result) {
    int Status = FAIL;
     if (strstr(*str, "cos") == *str || strstr(*str, "sin") == *str ||
        strstr(*str, "tan") == *str || strstr(*str, "ln") == *str) {
        *result = (*str)[0];
        (*str) += 3;
        if (*result == 'l') (*str)--;
        Status = SUCCESS;
    }
    if ((Status == FAIL) &&
        (strstr(*str, "acos") == *str || strstr(*str, "asin") == *str ||
         strstr(*str, "atan") == *str || strstr(*str, "sqrt") == *str)) {
        *result = (*str)[1];
        (*str) += 4;
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
    } else if (operator == ')') {
        result = 4;
    } else if (operator == '(') {
        result = 0;
    }
    return result;
}

int check_priority(char op1, char op2) {
    int Status = FAIL;
    int priority_op1 = get_priority(op1);
    int priority_op2 = get_priority(op2);
    if (priority_op1 > 0 && priority_op2 > 0 && 
        priority_op2 <= priority_op1) {
            Status = SUCCESS;
        }
    return Status;
}

int str_to_polish(char *str, Queue **res) {
    Stack *stack = stack_init();
    int Status = SUCCESS;
    double result = 1;
    while (*str && Status == SUCCESS) {
        remove_spaces(&str);
        Lexeme *lex = (Lexeme *) calloc (1, sizeof(Lexeme));
        lex->type = UNDEFINED;
        if (parse_num(&str, &result) == SUCCESS) {
            lex->type = NUMBER, lex->num = result;
            queue_push(*res, lex);
        } else if (parse_func(&str, &lex->chr) == SUCCESS) {
            lex->type = FUNCTION;
            stack_push(stack, lex);
        } else {
            if (parse_operator(&str, &lex->chr) == SUCCESS) lex->type = OPERATOR;
            else if (parse_bracket(&str, &lex->chr) == SUCCESS) lex->type = BRACKET;
            if (lex->chr == ')' && stack->size <= 0) {
                Status = FAIL;
                break;
            }
            Lexeme *seeked = stack_seek(stack);
            while (stack->size > 0 && seeked->type != NUMBER && lex->type != UNDEFINED) {
                seeked = stack_seek(stack);
                if (check_priority(seeked->chr, lex->chr) == SUCCESS || lex->chr == ')') {
                    if (seeked->chr == '(' && lex->chr == ')') {    
                        stack_pop(stack);
                        break;
                    } else {
                        queue_push(*res, stack_pop(stack));
                    }
                } else {
                    break;
                }
            }
            lex->type == UNDEFINED ? Status = FAIL : lex->chr != ')' ? stack_push(stack, lex) : 0;
        } 
        if (lex->type == UNDEFINED || Status == FAIL) free(lex);
    }
    while (stack->size > 0) {
        queue_push(*res, stack_pop(stack));
    }
    stack_free(stack);
    return Status;
}