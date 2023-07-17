#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define STACK_IS_NULL_ERROR "stack is null error\n"
#define STACK_NEW_LEXEME_IS_NULL_ERROR "stack new_lexeme is null error\n"
#define STACK_NEW_NODE_ALLOCATE_ERROR "stack new_node allocate error\n"
#define STACK_MEMORY_ALLOCATE_ERROR "stack allocate error\n"
#define STACK_IS_EMPTY_ERROR "stack is empty error\n"
#define LEXEME_MEMORY_ALLOCATE_ERROR

enum Type { NUMBER, OPERATOR, FUNCTION, BRACKET, UNDEFINED };

typedef struct Lexeme {
    enum Type type;
    unsigned char chr;
    double num;
} Lexeme;

typedef struct StackNode {
    Lexeme *lex;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    int size;
    StackNode *tail;
} Stack;

Stack *stack_init();
Lexeme *stack_pop(Stack *stack);
Lexeme *stack_seek(Stack *stack);
void stack_free(Stack *stack);
void stack_push(Stack *stack, Lexeme *New);


#endif  // SRC_STACK_H_
