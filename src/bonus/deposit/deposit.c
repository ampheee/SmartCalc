#include "deposit.h"

int calculate_deposit(DEPOSIT_STRUCT *deposit) {
    if (!deposit) {
        printf("Error: invalid deposit pointer\n");
        return FAIL;
    }
    if (deposit->deposit <= 0 || deposit->term <= 0 || 
    deposit->percent_rate < 0 || deposit->percent_rate > 100 || 
    deposit->tax_rate < 0 || deposit->tax_rate > 100 || 
    deposit->frequency_of_payment <= 0 || deposit->replenishment < 0 ||
    deposit->frequency_of_replanishment < 0 || deposit->withdrawal < 0 ||
    deposit->frequency_of_withdrawal < 0) {
        printf("Error\n");
        return FAIL;
    }
  long double sum = deposit->deposit;
  long double rate = (deposit->percent_rate / 12) / 100;
  long double tax = deposit->tax_rate / 100;
  long double cap = 0;

  for (int i = 0; i < deposit->term; i++) {
    long double accural = sum * rate;
    long double tax_sum = accural * tax;
    deposit->accrued_tax += tax_sum;
    deposit->accrued_deposit += accural - tax_sum;
    if (deposit->frequency_of_payment && deposit->capitalization_of_interest) {
      cap += accural - tax_sum;
      if (!((i + 1) % deposit->frequency_of_payment)) {
        sum += cap;
        cap = 0;
      }
    }
    if (deposit->replenishment && deposit->frequency_of_replanishment) {
      if (!((i + 1) % deposit->frequency_of_replanishment)) {
        sum += deposit->replenishment;
      }
    }
    if (deposit->withdrawal && deposit->frequency_of_withdrawal) {
      if (!((i + 1) % deposit->frequency_of_withdrawal)) {
        sum -= deposit->withdrawal;
      }
    }
  }

  if (deposit->capitalization_of_interest) {
    deposit->sum = deposit->deposit + deposit->accrued_deposit;
  } else {
    deposit->sum = deposit->deposit;
  }
  if (deposit->replenishment && deposit->frequency_of_replanishment)
    deposit->sum += deposit->replenishment * (int)(deposit->term / deposit->frequency_of_replanishment);
  if (deposit->withdrawal && deposit->frequency_of_withdrawal)
    deposit->sum -= deposit->withdrawal * (int)(deposit->term / deposit->frequency_of_withdrawal);
  return SUCCESS;
}
