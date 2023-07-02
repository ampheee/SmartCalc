#include "calculator.h"

int eval_expression(const gchar *expression) {
    return 0;
}

// int popL(LStack *stack) {
//     return 0;
// }

// int backL(L) {
//     return 0;
// }

int get_hash(Key *key) {
    int result;
    /* combine all inputs in some way */
    result = key->i * key->i + (key->p1.x * key->p1.x) - (key->p2.x * key->p2.x)
    /* make sure result isn't out of bounds of the array */
    return (result % SIZE_OF_MAP);
}