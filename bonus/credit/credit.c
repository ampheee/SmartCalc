#include "credit.h"

long double calculate_credit(long double credit, long double percent, int period,
                             int type, long double *firstPayment,
                             long double *lastPayment) {
    if (credit <= 0.1 || percent <= 0.1 || period <= 0 || type < 0 || type > 2 ||
        firstPayment == NULL || lastPayment == NULL) {
        fprintf(stderr, "Invalid input parameters\n");
        return FAIL;
    }
    long double monthlyPercent = percent / 100 / 12;
    long double annuityPayment = credit * monthlyPercent *
                                 powl(1 + monthlyPercent, period) /
                                 (powl(1 + monthlyPercent, period) - 1);
    long double totalAmount = annuityPayment * period;
    long double differentialPayment = credit / period + credit * monthlyPercent;

    if (type == ANNUITY) {
        *firstPayment = annuityPayment;
        *lastPayment = annuityPayment;
        return totalAmount;
    } else if (type == DIFFERENTIATED) {
        *firstPayment = differentialPayment;
        *lastPayment = differentialPayment + credit * monthlyPercent;
        return totalAmount;
    }

    fprintf(stderr, "Invalid payment type\n");
    return 0;
}
