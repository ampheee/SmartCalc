#ifndef _CREDIT_
#define _CREDIT_ // весьма удручающее объявление :(

#include "../../parse.h"
#include <math.h>

#define ANNUITY 1
#define DIFFERENTIATED 2


long double calculate_credit(long double credit, long double percent, int period,
                          int type, long double *firstPayment,
                          long double *lastPayment);

#endif  // _CREDIT_