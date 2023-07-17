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
    bool res = false;
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
        res = true;
    }
    return res;
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
    bool status = FAIL;
    size_t nums_count = 0;
    *result = s21_atof(str, &nums_count);
    if (nums_count != 0) {
        status = SUCCESS;
    }
    return status;
}

int parse_func(char **str, unsigned char *result) {
    int status = FAIL;
     if (strstr(*str, "cos") == *str || strstr(*str, "sin") == *str ||
        strstr(*str, "tan") == *str || strstr(*str, "ln") == *str) {
        (*str) += 3;
        *result = (*str)[0];
        if (*result == 'l') (*str)--;
    }
    if ((status == FAIL) &&
        (strstr(*str, "acos") == *str || strstr(*str, "asin") == *str ||
         strstr(*str, "atan") == *str || strstr(*str, "sqrt") == *str)) {
        (*str) += 4;
        *result = (*str)[1];
        if ((*str)[1] != 'q') *result -= 32;
    }
    if ((status == FAIL) && strstr(*str, "log") == *str) {
        (*str) += 3;
        *result = 'L';
    }
    return status;
}

int parse_operator(char **str, unsigned char *result) {
    int status = SUCCESS;
    printf("in function: %s\n", *str);
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
        status = FAIL;
    }
    if (status == SUCCESS) {
        (*str)++;
        if (*result == 'm') {
            (*str) += 2;
        }
    }
    return status;
}

int str_to_polish(char *str, Queue **res) {
    Stack *stack = stack_init();
    int status = SUCCESS;
    size_t len = strlen(str);
    printf("\nstart while cycle in str sizeof %lu chars\n", len);
    while (*str && status == SUCCESS) {
        Lexeme *lex = (Lexeme *) calloc (1, sizeof(Lexeme));
        if (isBasedDigit(*str, 10)) {
            double result = 1;
            status = parse_num(&str, &result);
            lex->type = NUMBER;
            lex->num = result;
        } else if (parse_operator(&str, &lex->chr)) {
            lex->type = OPERATOR;
        } else if (parse_func(&str, &lex->chr)) {
            lex->type = FUNCTION;
        }
        printf("check: lextype - %d, lexchar - %c, lexnum - %lf\n", lex->type, lex->chr, lex->num);
    }
    return status;
}