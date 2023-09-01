#ifndef SMARTCALC_QUEUE_H
#define SMARTCALC_QUEUE_H

#define QUEUE_IS_NULL_ERROR "queue is null error\n"
#define QUEUE_NEW_LEXEME_IS_NULL_ERROR "queue new_lexeme is null error\n"
#define QUEUE_NEW_NODE_ALLOCATE_ERROR "queue new_node allocate error\n"
#define QUEUE_ALLOCATE_ERROR "queue allocate error\n"
#define QUEUE_IS_EMPTY_ERROR "queue is empty error\n"

#include <stdlib.h>
#include "stack.h"

typedef struct QueNode {
    Lexeme *lex;
    struct QueNode *next;
} QueNode;

typedef struct Queue {
    int size;
    QueNode *head;
    QueNode *tail;
} Queue;

Queue *queue_init();
Lexeme *queue_pop(Queue *queue);
void queue_push(Queue *queue, Lexeme *New);
void queue_free(Queue *queue);
#endif //SMARTCALC_QUEUE_H
