#include "queue.h"

Queue *queue_init() {
    Queue *que = (Queue *) calloc (1, sizeof(Queue));
    if (que != NULL) {
        que->size = 0;
        que->head = NULL;
    } else {
        printf(QUEUE_ALLOCATE_ERROR);
    }
    return que;
}
Lexeme *queue_pop(Queue *queue) {
    Lexeme *popped = NULL;
    if (queue != NULL) {
        if (queue->size != 0) {
            QueNode *popped_node = queue->head;
            popped = popped_node->lex;
            queue->size--;
            queue->head = queue->head->next;
            free(popped_node);
        } else {
            printf(QUEUE_IS_EMPTY_ERROR);
        }
    } else {
        printf(QUEUE_IS_NULL_ERROR);
    }
    return popped;
}
Lexeme *queue_seek(Queue *queue) {
    QueNode *popped_node = NULL;
    Lexeme *popped_lex = NULL;
    if (queue != NULL) {
        if (queue->size >= 0) {
            popped_node = queue->head;
            if (popped_node != NULL) {
                popped_lex = popped_node->lex;
            }
        }
    }
    return popped_lex;
}
void queue_push(Queue *queue, Lexeme *new_lexeme) {
    if (queue != NULL) {
        QueNode *new_node = malloc(sizeof(QueNode));
        if (new_node != NULL) {
            new_node->lex = new_lexeme;
            new_node->next = NULL;
            if (queue->tail == NULL) {
                queue->head = new_node;
                queue->tail = new_node;
            } else {
                queue->tail->next = new_node;
                queue->tail = new_node;
            }
            queue->size++;
        } else if (new_node == NULL) {
            printf(QUEUE_NEW_NODE_ALLOCATE_ERROR);
        } else if (new_lexeme == NULL) {
            free(new_node);
            printf(QUEUE_NEW_LEXEME_IS_NULL_ERROR);
        }
    } else {
        printf(QUEUE_IS_NULL_ERROR);
    }
}
void queue_free(Queue *queue) {
    if (queue != NULL) {
        while (queue->head != queue->tail && queue->size != 0) {
            queue_pop(queue);
        }
    } else {
        printf(QUEUE_IS_NULL_ERROR);
    }
}
int queue_add_new_lex(Queue *queue, Lexeme new_value);