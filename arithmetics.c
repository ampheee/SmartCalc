#include "calculator.h"

int eval_expression(const gchar *expression) {
    return 0;
}

//realize: dijkstra polish notation
//output error or result

// int popL(LStack *stack) {
//     return 0;
// }

// int backL(L) {
//     return 0;
// }

int get_hash(Key *key) {
    int result;
    result = key->i * key->i + (key->p1.x * key->p1.x) - (key->p2.x * key->p2.x)
    return (result % SIZE_OF_MAP);
}