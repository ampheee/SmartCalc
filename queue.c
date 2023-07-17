#include "queue.h"

Queue *queue_init() {
    Queue *que = (Queue *) calloc (1, sizeof(Queue));
    if (que != NULL) {
        que->size = 0;
        que->tail = NULL;
    } else {
        printf(QUEUE_ALLOCATE_ERROR);
    }
    return que;
}
Lexeme *queue_pop(Queue *queue) {
    Lexeme *popped = NULL;
    if (queue != NULL) {
        if (queue->size != 0) {
            QueNode *popped_node = queue->tail;
            popped = popped_node->lex;
            queue->size--;
            queue->tail = queue->tail->prev;
            free(popped_node->lex);
            free(popped_node);
        }
    } else {
        printf(QUEUE_IS_NULL_ERROR);
    }
    return popped;
}
Lexeme *queue_seek(Queue *queue);
void queue_push(Queue *queue, Lexeme *New);
void queue_free(Queue *queue) {
    if (queue != NULL) {
        while (queue->tail != NULL && queue->size != 0) {
            QueNode *popped_node = queue->tail;
            queue->size--;
            queue->tail = queue->tail->next;
            free(popped_node->lex);
            free(popped_node);
        }
        free(queue);
    } else {
        printf(QUEUE_IS_NULL_ERROR);
    }
}
int queue_add_new_lex(Queue *queue, Lexeme new_value);