#include "calculator.h"

gchar *eval_expression(const gchar *expression) {
    Node *stack = {0};
    return 0;
}

bool is_based_digit(unsigned char c, unsigned int b) {
    bool res;
    if (b > 10) {
        res = (c >= '0' && c <= '9') || (c >= 'a' && c < 'a' + b - 10) ||
              (c >= 'A' && c < 'A' + b - 10);
    } else {
        res = c >= '0' && c < '0' + b;
    }
    return res;
}

void is_negative(bool *neg, char **sptr) {
    if (**sptr == '-') {
        (*sptr)++;
        *neg = true;
    } else if (**sptr == '+') {
        (*sptr)++;
    }
    if (**sptr == '-' || **sptr == '+') {
        (*sptr)--;
    }
}

bool is_exp(unsigned char **eval, int *e) {
    bool res = false;
    if (**eval == 'e' || **eval == 'E') {
        bool isNegative = 0;
        (*eval)++;
        if (**eval && **eval == '+') {
            (*eval)++;
        } else if (**eval && **eval == '-') {
            isNegative = true;
            (*eval)++;
        }
        while (**eval && is_based_digit(**eval, 10)) {
            *e = *e * 10 + (**eval - '0');
            (*eval)++;
        }
        if (isNegative) {
            *e *= -1;
        }
        res = true;
    }
    return res;
}

ERROR parse_num_string(unsigned char **result, char **eval) {
    unsigned numsCount = 0;
    bool sign = false, found = SUCCESS;
    while (**eval && (is_based_digit(**eval, 10) || **eval == '.') ||
        **eval == '-' || **eval == '+') {
        if (!sign && (**eval == '+' || **eval == '-')) sign = true;
        else if (sign && (**eval == '+' || **eval == '-')) break; found = FAIL;
        **result = **eval;
        (*result)++;
        numsCount++;
        (*eval)++;
    }
    if (found == SUCCESS) **result = ' ';
    return found;
}

int get_priority(gchar c) {
    if (c == '(') return 0;
    else if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else if (c == '^') return 3;
    else if (c == '~') return 4;
}

int pushToStack(Stack *stack, gchar L) {
    Node *newNode = (Node *) calloc(1, sizeof(Node));
    if (newNode == NULL) {
        return FAIL;
    }
    if (stack->size != 0) {
        newNode->next = stack->tail;
        stack->tail = newNode;
    } else {
        stack->tail = newNode;
    }
    stack->size++;
    return SUCCESS;
}

int popFromStack(Stack *stack) {
    if (stack->size > 0) {
        Node *tempNode = stack->tail;
        unsigned char c = tempNode->L;
        if (stack->size == 1) {
            stack->tail = NULL;
        } else {
            stack->tail = tempNode->next;
        }
        stack->size--;
        free(tempNode);
        return c;
    }
    return FAIL;
}

int seekFromStack(Stack *stack) {
    if (stack->size > 0) {
        return stack->tail->L;
    }
    return FAIL;
}


int *toPostFix(unsigned char *postString, gchar *eval) {
    for (unsigned i = 0; i < strlen(eval); i++) {
        unsigned char c = eval[i];
        if (is_based_digit(c, 10)) {
            unsigned char num[100] = {0};
            parse_num_string((unsigned char **) &num, &eval);
        }
    }
}

