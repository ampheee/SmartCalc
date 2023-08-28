#include "credit.h"

long double total_payment(long double loan, long double interestRate, int term,
                          int type, long double *firstPayment,
                          long double *lastPayment) {
  long double totalPayment = 0;
  if (loan < 0.01 || interestRate < 0.01 || term < 1 || !firstPayment ||
      !lastPayment) {
    totalPayment = FAIL;
  } else {
    long double payment = 0;
    long double monthlyInterest = (interestRate / 100.00) / 12.00;
    if (type == ANNUITY) {
      payment = loan *
                (monthlyInterest +
                 (monthlyInterest /
                  ((pow((1.00 + monthlyInterest), (long double)term) - 1.00))));
      *firstPayment = *lastPayment = payment;
      totalPayment = payment * term;
    } else if (type == DIFFERENTIATED) {
      long double mainPayment = loan / term;
      long double alreadyRepaid = 0;
      long double restOfLoan = loan;
      for (int i = 0; i < term; i++) {
        alreadyRepaid = mainPayment * i;
        restOfLoan = loan - alreadyRepaid;
        payment = mainPayment + restOfLoan * monthlyInterest;
        totalPayment += payment;
        if (i == 0) *firstPayment = payment;
        if (i == term - 1) *lastPayment = payment;
      }
    } else {
      totalPayment = FAIL;
    }
  }
  return totalPayment;
}