#ifndef _CALLBACKS_
#define _CALLBACKS_

#include <gtk-3.0/gtk/gtk.h>
#include "parse.h"
#include "arithmetics.h"
#include "interface.h"
#include "../bonus/credit/credit_callbacks.h"
#include "../bonus/deposit/deposit_callbacks.h"
#include "graph_callbacks.h"

void on_insert_text_float(GtkEditable *editable, const gchar *text, gint length);
void on_insert_text_int(GtkEditable *editable, const gchar *text, gint length);

void setup_entry(GtkWidget *entry);

void setup_credentials(GtkWidget *grid, int col, int row,
                        int width, int heigth);

double convert_entry_to_num(GtkWidget *entry);

void connect_entry(GtkWidget *grid, GtkWidget *entry, int col, int row, 
                            int width, int heigth,  gboolean parse_int);

void on_digit_func_button_clicked(GtkButton *button, gpointer user_data);
void on_clear_button_clicked(GtkButton *button, gpointer user_data);
void on_equal_button_clicked(GtkButton *button, gpointer user_data);
void on_credit_button_clicked();
void on_deposit_button_clicked();
void on_graph_button_clicked(GtkWidget *button, gpointer user_data);


#endif