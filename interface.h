#ifndef SMARTCALC_INTERFACE_H_
#define SMARTCALC_INTERFACE_H_

#include "calculator.h"
#include "queue.h"
#include "stack.h"

void on_digit_button_clicked(GtkButton *button, gpointer user_data);
void on_clear_button_clicked(GtkButton *button, gpointer user_data);
void on_equal_button_clicked(GtkButton *button, gpointer user_data);
void on_credit_button_clicked(GtkButton *button, gpointer user_data);
void on_graphics_button_clicked(GtkButton *button, gpointer user_data);


#endif  //SMARTCALC_INTERFACE_H_