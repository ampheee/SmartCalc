#ifndef _CALLBACKS_
#define _CALLBACKS_

#include <gtk-3.0/gtk/gtk.h>
#include "parse.h"
#include "arithmetics.h"

void on_digit_func_button_clicked(GtkButton *button, gpointer user_data);
void on_clear_button_clicked(GtkButton *button, gpointer user_data);
void on_equal_button_clicked(GtkButton *button, gpointer user_data);
void on_credit_button_clicked(GtkButton *button, gpointer user_data);
void on_graphics_button_clicked(GtkButton *button, gpointer user_data);

#endif