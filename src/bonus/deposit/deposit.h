#ifndef _DEPOSIT_
#define _DEPOSIT_ 

#include "../../modules/parse.h"
#include "deposit.h"

typedef struct _DEPOSIT_STRUCT {
  double deposit;
  int term;
  double percent_rate;
  double tax_rate;
  int frequency_of_payment;
  int capitalization_of_interest;
  double replenishment;
  int frequency_of_replanishment;
  double withdrawal;
  int frequency_of_withdrawal;
  double accrued_deposit;
  double accrued_tax;
  double sum;
} DEPOSIT_STRUCT;

int calculate_deposit(DEPOSIT_STRUCT *deposit);


#endif // _DEPOSIT_