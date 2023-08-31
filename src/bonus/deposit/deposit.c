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
    double balance = deposit->deposit;
    for(int i = 1; i <= deposit->term; i++) {
      double interest = balance * (deposit->percent_rate / 100) / deposit->frequency_of_payment;
    if(deposit->capitalization_of_interest > 0 && i % deposit->capitalization_of_interest == 0) {
      balance += interest;
    }
    if(deposit->frequency_of_replanishment > 0 && i % deposit->frequency_of_replanishment == 0) {
      balance += deposit->replenishment;
    }
    if(deposit->frequency_of_withdrawal > 0 && i % deposit->frequency_of_withdrawal == 0) {
      if(balance < deposit->withdrawal) {
        return FAIL;
      } 
      balance -= deposit->withdrawal;
    }
    balance += interest;
    double tax = interest * (deposit->tax_rate / 100);
    deposit->accrued_tax += tax;
    balance -= tax;
    deposit->accrued_deposit += interest;
    deposit->sum = balance;
  }
  printf("accrued deposit: %lf, sum: %lf", deposit->accrued_deposit, deposit->sum);
  return SUCCESS;
}
