#include "credit_callbacks.h"

GtkWidget *credit;
GtkWidget *term_credit;
GtkWidget *percent_credit;
int type_credit = ANNUITY;
GtkWidget *monthly_payment_credit;
GtkWidget *overpay_credit;
GtkWidget *sum_credit;

void init_buttons_credit(GtkWidget *grid) {
  const gchar *labels[] = {
      "Credit:", "Period term:", "Percent rate:", "Type:",
      "Payment | Monthly:", "Overlay:", "Total:", "powered by babbling\n\tschool21 | 2023"
    };
    for (int row = 0; row < 8; row++) {
      GtkWidget *label = gtk_button_new_with_label(labels[row]);
      gtk_grid_attach(GTK_GRID(grid), label, 0, row, 1, 1);
      gtk_widget_set_sensitive(label, FALSE);
    }
    GtkWidget *annuity = gtk_radio_button_new_with_label(NULL, "ANNUITY");
    g_signal_connect(annuity, "toggled", G_CALLBACK(on_annuity_radio_clicked), "ANNUITY");
    gtk_grid_attach(GTK_GRID(grid), annuity, 1, 3, 1, 1);
    GtkWidget *differentiated = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(annuity), "DIFFERENTIATED");
    g_signal_connect(differentiated, "toggled", G_CALLBACK(on_differentiated_radio_clicked), "DIFFERENTIATED");
    gtk_grid_attach(GTK_GRID(grid), differentiated, 2, 3, 1, 1);
    GtkWidget *calculate_button = gtk_button_new_with_label("Calculate");
    gtk_grid_attach(GTK_GRID(grid), calculate_button, 1, 7, 2, 1);
    g_signal_connect(calculate_button, "clicked", G_CALLBACK(on_calculate_credit_button_clicked), grid);
    monthly_payment_credit = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), monthly_payment_credit, 2, 4, 1, 1);
    overpay_credit =  gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), overpay_credit, 2, 5, 1, 1);
    sum_credit = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), sum_credit, 2, 6, 1, 1);
}

void init_entries_credit(GtkWidget *grid) {
  credit = gtk_entry_new();
  connect_entry(grid, credit, 1, 0, 2, 1, false);
  term_credit = gtk_entry_new();
  connect_entry(grid, term_credit, 1, 1, 2, 1, true);
  percent_credit = gtk_entry_new();
  connect_entry(grid, percent_credit, 1, 2, 2, 1, false);
}

void on_credit_button_clicked() {
  GtkWidget *window_new = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window_new), "Credit calculator");
  gtk_window_set_default_size(GTK_WINDOW(window_new), 400, 300);
  gtk_window_set_resizable(GTK_WINDOW(window_new), FALSE);
  GtkWidget *box_new = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window_new), box_new);
  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_box_pack_start(GTK_BOX(box_new), grid, TRUE, TRUE, 0);
  init_entries_credit(grid);
  init_buttons_credit(grid);
  gtk_widget_show_all(window_new);
}

void on_calculate_credit_button_clicked() {
  long double total_payment_output = 0;
  long double first_payment = 0;
  long double last_payment = 0;
  char string_buffer[64] = {};
  long double double_credit = convert_entry_to_num(credit);
  long double double_percent = convert_entry_to_num(percent_credit);
  int int_period = convert_entry_to_num(term_credit);
  total_payment_output = calculate_credit(double_credit, double_percent, int_period,
                                        type_credit, &first_payment, &last_payment);
  sprintf(string_buffer, "%.2Lf", total_payment_output);
  gtk_label_set_text(GTK_LABEL(sum_credit), total_payment_output >= 0 ? string_buffer : "INCORRECT!");
  if (first_payment == last_payment) {
    memset(string_buffer, 0, sizeof(string_buffer));
    sprintf(string_buffer, "%.2Lf", first_payment);
    gtk_label_set_text(GTK_LABEL(monthly_payment_credit), total_payment_output >= 0 ? string_buffer : "INCORRECT!");
  } else {
    char buffer_2[64];
    sprintf(string_buffer, "%.2Lf", first_payment);
    strcat(string_buffer, " ... ");
    sprintf(buffer_2, "%.2Lf", last_payment);
    strcat(string_buffer, buffer_2);
    gtk_label_set_text(GTK_LABEL(monthly_payment_credit), string_buffer);
  }
  memset(string_buffer, 0, sizeof(string_buffer));
  sprintf(string_buffer, "%.2Lf", total_payment_output - double_credit);
  gtk_label_set_text(GTK_LABEL(overpay_credit), total_payment_output >= 0 ? string_buffer : "INCORRECT!");
}

void on_differentiated_radio_clicked() {
  type_credit = DIFFERENTIATED;
}

void on_annuity_radio_clicked() { 
  type_credit = ANNUITY;
}
