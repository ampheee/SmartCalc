#include "debug.h"

//void print_queue(Queue *queue) {
//    if (queue != NULL) {
//        while (queue->tail !=);
//    }
//}

void print_stack(Stack *stack) {
    if (stack != NULL) {
        while (stack->tail != NULL && stack->size != 0) {
            Lexeme *popped = stack_pop(stack);
            printf("Lexeme char: %c | Lexeme number: %lf | stack size: %d",
                popped->chr, popped->num, stack->size);
            free(popped);
        }
        if (stack->size == 0) {
            printf("stack is empty");
        }
    } else {
        printf(STACK_IS_NULL_ERROR);
    }
}