#ifndef _DEPOSIT_CALLBACKS_
#define _DEPOSIT_CALLBACKS_

#include "deposit.h"
#include "../../modules/callbacks.h"

void init_buttons_deposit(GtkWidget *grid);
void init_entries_deposit(GtkWidget *grid);
void init_labels_deposit(GtkWidget *grid);

void on_calculate_deposit_button_clicked();
void on_capitalization_clicked();

#endif //_DEPOSIT_CALLBACKS_