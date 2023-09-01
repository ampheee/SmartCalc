#include "credit.h"

long double calculate_credit(long double credit, long double percent, int term,
                             int type, long double *first_payment,
                             long double *last_payment) {
    if (credit <= 0.1 || percent <= 0.1 || term <= 0 || type < 0 || type > 2 ||
        first_payment == NULL || last_payment == NULL) {
        return FAIL;
    }
    long double monthly_percent = percent / 100 / 12;
    long double annuity_payment = credit * monthly_percent *
                                 powl(1 + monthly_percent, term) /
                                 (powl(1 + monthly_percent, term) - 1);
    long double total_amount = annuity_payment * term;
    long double differential_payment = credit / term + credit * monthly_percent;
    if (type == ANNUITY) {
        *first_payment = annuity_payment;
        *last_payment = annuity_payment;
    } else if (type == DIFFERENTIATED) {
      long double monthly_payment = credit / term;
      long double payment;
      long double paid = 0;
      long double rest = credit;
      total_amount = 0;
      for (int i = 0; i < term; i++) {
        paid = monthly_payment * i;
        rest = credit - paid;
        payment = monthly_payment + rest * monthly_percent;
        total_amount += payment;
      }
        *first_payment = differential_payment;
        *last_payment = differential_payment + credit * monthly_percent;
    }
    return total_amount;
}
