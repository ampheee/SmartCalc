#ifndef _DEPOSIT_
#define _DEPOSIT_ 

#include "../parse.h"

typedef struct {
  long double amount;
  int term;
  long double interest_rate;
  long double tax_rate;
  int periodicity;
  int capitalization;
  long double replenishment;
  int freq_of_replen;
  long double withdrawal;
  int freq_of_withd;
  // output
  long double accrued_interest;
  long double tax_amount;
  long double amount_by_end;
} s_deposit;

#endif // _DEPOSIT_