#include "deposit.h"

void deposit_calculation(s_deposit *d) {
  d->accrued_interest = 0;
  d->tax_amount = 0;
  long double sum = d->amount;
  long double rate = (d->interest_rate / 12) / 100;
  long double tax = d->tax_rate / 100;
  long double cap_sum = 0;
  for (int i = 0; i < d->term; i++) {
    long double accural = sum * rate;
    long double tax_sum = accural * tax;
    d->tax_amount += tax_sum;
    d->accrued_interest += accural - tax_sum;
    if (d->periodicity && d->capitalization) {
      cap_sum += accural - tax_sum;
      if (!((i + 1) % d->periodicity)) {
        sum += cap_sum;
        cap_sum = 0;
      }
    }
    if (d->replenishment && d->freq_of_replen) {
      if (!((i + 1) % d->freq_of_replen)) {
        sum += d->replenishment;
      }
    }
    if (d->withdrawal && d->freq_of_withd) {
      if (!((i + 1) % d->freq_of_withd)) {
        sum -= d->withdrawal;
      }
    }
  }
  if (d->capitalization) {
    d->amount_by_end = d->amount + d->accrued_interest;
  } else {
    d->amount_by_end = d->amount;
  }
  if (d->replenishment && d->freq_of_replen)
    d->amount_by_end += d->replenishment * (int)(d->term / d->freq_of_replen);
  if (d->withdrawal && d->freq_of_withd)
    d->amount_by_end -= d->withdrawal * (int)(d->term / d->freq_of_withd);
}
