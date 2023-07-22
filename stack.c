#include "stack.h"

Stack *stack_init() {
    Stack *stack = (Stack *) calloc (1, sizeof(Stack));
    if (stack != NULL) {
        stack->size = 0;
        stack->tail = NULL;
    } else {
        printf(STACK_MEMORY_ALLOCATE_ERROR);
    }
    return stack;
}
Lexeme *stack_pop(Stack *stack) {
    Lexeme *result = NULL;
    if (stack != NULL && stack->size > 0) {
        if (stack->tail != NULL && stack->tail->lex != NULL) {
            StackNode *popped = stack->tail;
            stack->tail = stack->tail->next;
            result = popped->lex;
            stack->size--;
            free(popped);
        } else if (stack->tail == NULL) {
            printf("stack tail is null error\n");
        } else if (stack->tail->lex == NULL) {
            printf("stack tail lex is null\n");
        }
    } else if (stack == NULL) {
        printf(STACK_IS_NULL_ERROR);
    }
    return result;
}
Lexeme *stack_seek(Stack *stack) {
    Lexeme *result = NULL;
    if (stack != NULL && stack->size > 0) {
        result = stack->tail->lex;
    } else if (stack == NULL){
        printf(STACK_IS_NULL_ERROR);
    } else if (stack->size < 0) {
        printf(STACK_IS_EMPTY_ERROR);
    }
    return result;
}
void stack_free(Stack *stack) {
    if (stack != NULL) {
        while (stack->tail != NULL && stack->size > 0) {
            Lexeme *popped = stack_pop(stack);
            free(popped);
        }
    } else {
        printf(STACK_IS_NULL_ERROR);
    }
}
void stack_push(Stack *stack, Lexeme *new_lexeme) {
    if (stack != NULL) {
        StackNode *new_node = (StackNode *) calloc(1, sizeof(StackNode));
        if (new_node != NULL && new_lexeme != NULL) {
            new_node->lex = new_lexeme;
            if (stack->size > 0) {
                StackNode *prev = stack->tail;
                stack->tail = new_node;
                stack->tail->next = prev;
            } else if (stack->size == 0) {
                stack->tail = new_node;
                stack->tail->next = NULL;
            }
            stack->size++;
        } else if (new_node == NULL) {
            printf(STACK_NEW_NODE_ALLOCATE_ERROR);
        } else if (new_lexeme == NULL) {
            free(new_node);
            printf(STACK_NEW_LEXEME_IS_NULL_ERROR);
        }
    } else {
        printf(STACK_IS_NULL_ERROR);
    }
}
