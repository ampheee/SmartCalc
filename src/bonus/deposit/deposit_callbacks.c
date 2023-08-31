#include "deposit_callbacks.h"


GtkWidget *deposit;
GtkWidget *term_deposit;
GtkWidget *percent_rate_deposit;
GtkWidget *tax_rate_deposit;
GtkWidget *frequency_of_payments_deposit;
GtkWidget *capitalization_deposit;
GtkWidget *replenishment_deposit;
GtkWidget *frequency_of_replenishment_deposit;
GtkWidget *withdrawal_deposit;
GtkWidget *frequency_of_withdrawal_deposit;
GtkWidget *accrued_deposit;
GtkWidget *accrued_tax_deposit;
GtkWidget *sum_deposit;
bool capitalization = false;

void init_buttons_deposit(GtkWidget *grid) {
  const gchar *labels[] = {
      "Deposit: ", "Deposit term:", "Percent rate:", 
      "Tax rate:", "Frequency of payments:", "Capitalization of interest",
      "Replenishment:", "Frequency of replenishment:", "Withdrawal:",
      "Frequency of Withdrawal:", "Accrued sum:", "Accrued tax: ", "Total: ",
      "powered by babbling\n\tschool21 | 2023"
  };
  for (int row = 0; row < 14; row++) {
      GtkWidget *label = gtk_button_new_with_label(labels[row]);
      gtk_grid_attach(GTK_GRID(grid), label, 0, row, 1, 1);
      gtk_widget_set_sensitive(label, FALSE);
  }
  GtkWidget *credentials_button = gtk_button_new_with_label("powered by babbling\n\tschool21 | 2023");
  gtk_grid_attach(GTK_GRID(grid), credentials_button, 0, 7, 1, 1);
}

void connect_entry(GtkWidget *grid, GtkWidget *entry, int col, int row, 
                            int width, int heigth,  gboolean parse_int) {
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);
    gtk_entry_set_max_length(GTK_ENTRY(entry), 255);
    if (parse_int) {
      g_signal_connect(G_OBJECT(entry), "insert-text", G_CALLBACK(on_insert_text_int), NULL);
    } else {
      g_signal_connect(G_OBJECT(entry), "insert-text", G_CALLBACK(on_insert_text_float), NULL);
    }
    gtk_grid_attach(GTK_GRID(grid), entry, col, row, width, heigth);
}

void init_entries_deposit(GtkWidget *grid) {
  deposit = gtk_entry_new();
  connect_entry(grid, deposit, 1, 0, 1, 1, false);
  term_deposit = gtk_entry_new();
  connect_entry(grid, term_deposit, 1, 1, 1, 1, true);
  percent_rate_deposit = gtk_entry_new();
  connect_entry(grid, percent_rate_deposit, 1, 2, 1, 1, false);
  tax_rate_deposit = gtk_entry_new();
  connect_entry(grid, tax_rate_deposit, 1, 3, 1, 1, false);
  frequency_of_payments_deposit = gtk_entry_new();
  connect_entry(grid, frequency_of_payments_deposit, 1, 4, 1, 1, true);
  replenishment_deposit = gtk_entry_new();
  connect_entry(grid, replenishment_deposit, 1, 6, 1, 1, false);
  frequency_of_replenishment_deposit  =  gtk_entry_new();
  connect_entry(grid, frequency_of_replenishment_deposit, 1, 7, 1, 1, true);
  withdrawal_deposit = gtk_entry_new();
  connect_entry(grid, withdrawal_deposit, 1, 8, 1, 1, false);
  frequency_of_withdrawal_deposit = gtk_entry_new();
  connect_entry(grid, frequency_of_withdrawal_deposit, 1, 9, 1, 1, false);
  capitalization_deposit = gtk_check_button_new_with_label("Enable");
  gtk_grid_attach(GTK_GRID(grid), capitalization_deposit, 1, 5, 1, 1);
  g_signal_connect(capitalization_deposit, "toggled", G_CALLBACK(on_capitalization_clicked), NULL);
}

void init_labels_deposit(GtkWidget *grid) {
  accrued_deposit = gtk_label_new("");
  accrued_tax_deposit = gtk_label_new("");
  sum_deposit = gtk_label_new("");
  gtk_grid_attach(GTK_GRID(grid), accrued_deposit, 1, 10, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), accrued_tax_deposit, 1, 11, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), sum_deposit, 1, 12, 1, 1);
  GtkWidget *calculate_button = gtk_button_new_with_label("Calculate");
  gtk_grid_attach(GTK_GRID(grid), calculate_button, 1, 13, 1, 1);
  g_signal_connect(calculate_button, "clicked", G_CALLBACK(on_calculate_deposit_button_clicked), grid);
}

void on_deposit_button_clicked() {
    GtkWidget *window_new = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window_new), "Deposit calculator");
    gtk_window_set_default_size(GTK_WINDOW(window_new), 400, 300);
    gtk_window_set_resizable(GTK_WINDOW(window_new), FALSE);
    GtkWidget *box_new = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window_new), box_new);
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_box_pack_start(GTK_BOX(box_new), grid, TRUE, TRUE, 0);
    init_entries_deposit(grid);
    init_buttons_deposit(grid);
    init_labels_deposit(grid);
    gtk_widget_show_all(window_new);
}

void parse_to_struct_deposit(DEPOSIT_STRUCT *dep) {
  dep->deposit = convert_entry_to_num(deposit);
  dep->term = (int) convert_entry_to_num(term_deposit);
  dep->percent_rate = convert_entry_to_num(percent_rate_deposit);
  dep->tax_rate = convert_entry_to_num(tax_rate_deposit);
  dep->frequency_of_payment = (int) convert_entry_to_num(frequency_of_payments_deposit);
  dep->replenishment = convert_entry_to_num(replenishment_deposit);
  dep->frequency_of_replanishment = (int) convert_entry_to_num(frequency_of_replenishment_deposit);
  dep->withdrawal = convert_entry_to_num(withdrawal_deposit);
  dep->capitalization_of_interest = capitalization;
}

void on_calculate_deposit_button_clicked() {
  DEPOSIT_STRUCT dep = {0};
  parse_to_struct_deposit(&dep);
  int Status = calculate_deposit(&dep);
  char buffer[256] = {0};
  if (Status == FAIL) {
    sprintf(buffer, "%.2f", dep.accrued_deposit);
    gtk_label_set_text(GTK_LABEL(accrued_deposit), buffer);
    memset(buffer, 0, 256);
    sprintf(buffer, "%.2f", dep.accrued_tax);
    gtk_label_set_text(GTK_LABEL(accrued_tax_deposit), buffer);
    memset(buffer, 0, 256);
    sprintf(buffer, "%.2f", dep.sum); 
    gtk_label_set_text(GTK_LABEL(sum_deposit), buffer);
  } else { 
    gtk_label_set_text(GTK_LABEL(accrued_deposit), "ERROR!");
    gtk_label_set_text(GTK_LABEL(accrued_tax_deposit), "ERROR!");
    gtk_label_set_text(GTK_LABEL(sum_deposit), "ERROR!");

  }
}

void on_capitalization_clicked() {
  capitalization = !capitalization;
};