#include "debug.h"

void print_queue(Queue *queue) {
   if (queue != NULL) {
        QueNode *current = queue->head;
        while (current != NULL) {
            printf("QueNode Type: %d | QueNode char: %c | QueNode num: %lf\n", 
            current->lex->type, current->lex->chr, current->lex->num);
            current = current->next;
        }
        if (queue->size == 0) {
            // printf(QUEUE_IS_EMPTY_ERROR);
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
            // printf(STACK_IS_EMPTY_ERROR);
        }
    } else {
        printf(STACK_IS_NULL_ERROR);
    }
}