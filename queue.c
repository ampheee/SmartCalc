#include "queue.h"

Queue *queue_init() {
    Queue *que := (Queue *) calloc (1, sizeof(Queue));
    if (que != NULL) {
    } else {
        printf(QUEUE_ALLOCATE_ERROR);
    }
}
Lexeme *queue_pop(Queue *New);
Lexeme *queue_seek(Queue *New);
void queue_push(Queue *queue, Lexeme *New);
void queue_free(Queue *queue);
bool queue_add_new_lex(Queue *queue, Lexeme new_value);