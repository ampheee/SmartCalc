#include "debug.h"

void print_queue(Queue *queue) {
   if (queue != NULL) {
        while (queue->size != 0) {
            Lexeme *popped = queue_pop(queue);
            printf("QueLexeme char: %c | QueLexeme number: %.7lf | QueSize: %5d\n",
                popped->chr, popped->num, queue->size + 1);
            free(popped);
        }
        if (queue->size == 0) {
            printf(QUEUE_IS_EMPTY_ERROR);
        }
    } else {
        printf(QUEUE_IS_NULL_ERROR);
    }
}

void print_stack(Stack *stack) {
    if (stack != NULL) {
        while (stack->size != 0) {
            Lexeme *popped = stack_pop(stack);
            printf("Lexeme char: %c | Lexeme number: %lf | stack size: %d\n",
                popped->chr, popped->num, stack->size + 1);
            // free(popped);
        }
        if (stack->size == 0) {
            printf(STACK_IS_EMPTY_ERROR);
        }
    } else {
        printf(STACK_IS_NULL_ERROR);
    }
}