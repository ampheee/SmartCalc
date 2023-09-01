#ifndef _CREDIT_CALLBACKS_
#define _CREDIT_CALLBACKS_

#include "../../modules/callbacks.h"
#include "credit.h"

#define ANNUITY 1
#define DIFFERENTIATED 2
void init_entries_credit(GtkWidget *grid);
void init_buttons_credit(GtkWidget *grid);

void on_calculate_credit_button_clicked();

void on_differentiated_radio_clicked();
void on_annuity_radio_clicked();

#endif