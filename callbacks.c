#include "callbacks.h"
#include "bonus/credit/credit.h"


void on_digit_func_button_clicked(GtkButton *button, gpointer user_data) {
    const gchar *digit = gtk_button_get_label(button);
    GtkEntry *entry = GTK_ENTRY(user_data);
    const gchar *current_text = gtk_entry_get_text(entry);
    gchar *new_text = g_strconcat(current_text, digit, NULL);
    gtk_entry_set_text(entry, new_text);
    g_free(new_text);
}

void on_clear_button_clicked(GtkButton *button, gpointer user_data) {
    GtkEntry *entry = GTK_ENTRY(user_data);
    gtk_entry_set_text(entry, "");
}

void on_equal_button_clicked(GtkButton *button, gpointer user_data) {
    GtkEntry *entry = GTK_ENTRY(user_data);
    gchar input[256] = {0};
    const gchar *current_text = gtk_entry_get_text(entry);
    g_print("%s\n", current_text);
    snprintf(input, sizeof(input), "%s", current_text);
    Queue *res_que = queue_init();
    if (str_to_polish(input, &res_que) == SUCCESS) {
        int Status = SUCCESS;
        gtk_entry_set_text(entry, "");
        double result = calculate(res_que, 0, &Status);
        if (Status == SUCCESS) {
            gchar result_str[256] = {0};
            sprintf(result_str, "%f", result);
            gtk_entry_set_text(entry, result_str);
        } else {
            gtk_entry_set_text(entry, "error\n");
        }
    } else {
        gtk_entry_set_text(entry, "error\n");
    }
    queue_free(res_que);
    free(res_que);
}

// bonus part 1
GtkWidget *credit;
GtkWidget *period_credit;
GtkWidget *percent_credit;
int type_credit = ANNUITY;
GtkWidget *monthly_payment_credit;
GtkWidget *overpay_credit;
GtkWidget *sum_credit;

static void on_insert_text_float(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer user_data) {
    for (int i = 0; i < length; i++) {
        if (!g_ascii_isdigit(text[i]) && text[i] != '.') {
            g_signal_stop_emission_by_name(editable, "insert-text");
            return;
        }
    }
}

static void on_insert_text_int(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer user_data) {
    for (int i = 0; i < length; i++) {
        if (!g_ascii_isdigit(text[i])) {
            g_signal_stop_emission_by_name(editable, "insert-text");
            return;
        }
    }
}

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
    monthly_payment_credit = gtk_label_new("Monthly payment");
    gtk_grid_attach(GTK_GRID(grid), monthly_payment_credit, 2, 4, 1, 1);
    overpay_credit =  gtk_label_new("Amount of the overpayment");
    gtk_grid_attach(GTK_GRID(grid), overpay_credit, 2, 5, 1, 1);
    sum_credit = gtk_label_new("Total sum");
    gtk_grid_attach(GTK_GRID(grid), sum_credit, 2, 6, 1, 1);
}

void init_entries_credit(GtkWidget *grid) {
  credit = gtk_entry_new();
  gtk_entry_set_alignment(GTK_ENTRY(credit), 1);
  gtk_entry_set_max_length(GTK_ENTRY(credit), 255);
  g_signal_connect(G_OBJECT(credit), "insert-text", G_CALLBACK(on_insert_text_float), NULL);
  gtk_grid_attach(GTK_GRID(grid), credit, 1, 0, 2, 1);
  period_credit = gtk_entry_new();
  gtk_entry_set_alignment(GTK_ENTRY(period_credit), 1);
  gtk_entry_set_max_length(GTK_ENTRY(period_credit), 255);
  g_signal_connect(G_OBJECT(period_credit), "insert-text", G_CALLBACK(on_insert_text_int), NULL);
  gtk_grid_attach(GTK_GRID(grid), period_credit, 1, 1, 2, 1);
  percent_credit = gtk_entry_new();
  gtk_entry_set_alignment(GTK_ENTRY(percent_credit), 1);
  gtk_entry_set_max_length(GTK_ENTRY(percent_credit), 255);
  g_signal_connect(G_OBJECT(percent_credit), "insert-text", G_CALLBACK(on_insert_text_float), NULL);
  gtk_grid_attach(GTK_GRID(grid), percent_credit, 1, 2, 2, 1);
}

void on_credit_button_clicked(GtkButton *button, gpointer user_data) {
  GtkWidget *window_new = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window_new), "Credit calculator");
  gtk_window_set_default_size(GTK_WINDOW(window_new), 400, 300);
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

void on_calculate_credit_button_clicked(GtkButton *button, gpointer user_data) {
  long double total_payment_output = 0;
  long double first_payment = 0;
  long double last_payment = 0;
  size_t nums = 0;
  char string_buffer[64] = {};
  gchar *credit_buffer = (gchar *) calloc (256, sizeof(gchar));
  gchar *percent_buffer = (gchar *) calloc (256, sizeof(gchar));
  gchar *period_buffer = (gchar *) calloc (256, sizeof(gchar));
  const gchar *str_credit = gtk_entry_get_text(GTK_ENTRY(credit));
  const gchar *str_percent = gtk_entry_get_text(GTK_ENTRY(percent_credit));
  const gchar *str_period = gtk_entry_get_text(GTK_ENTRY(period_credit));
  snprintf(credit_buffer, sizeof(credit_buffer), "%s", str_credit);
  snprintf(percent_buffer, sizeof(percent_buffer), "%s", str_percent);
  snprintf(period_buffer, sizeof(period_buffer), "%s", str_period);
  long double double_credit = parse_to_float(&credit_buffer, &nums);
  long double double_percent = parse_to_float(&percent_buffer, &nums);
  int int_period = parse_to_float(&period_buffer, &nums);
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

void on_differentiated_radio_clicked(GtkWidget *radio, gpointer user_data) {
  type_credit = DIFFERENTIATED;
}

void on_annuity_radio_clicked(GtkWidget *radio, gpointer user_data) { 
  type_credit = ANNUITY;
}


// bonus part 2

GtkWidget *deposit;
GtkWidget *term_deposit;
GtkWidget *percent_rate_deposit;
GtkWidget *tax_rate_deposit;
GtkWidget *frequency_of_payments_deposit;
GtkWidget *capitalization_of_interest_deposit;
GtkWidget *replenishment_deposit;
GtkWidget *frequency_of_replenishment_deposit;
GtkWidget *Withdrawal;
GtkWidget *frequency_of_withdrawal;
GtkWidget *accrued_deposit;
GtkWidget *accrued_tax_deposit;
GtkWidget *sum_deposit;

void init_buttons_deposit(GtkWidget *grid) {
  const gchar *labels[] = {
      "Deposit: ", "Deposit term:", "Percent rate:", 
      "Tax rate:", "Frequency of payments:", "Capitalization of interest:",
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

void connect_button(GtkWidget *button, GtkWidget *grid, gboolean parse_int,)

void init_entries_deposit(GtkWidget *grid) {
  deposit = gtk_entry_new();
  gtk_entry_set_alignment(GTK_ENTRY(deposit), 1);
  gtk_entry_set_max_length(GTK_ENTRY(deposit), 255);
  g_signal_connect(G_OBJECT(deposit), "insert-text", G_CALLBACK(on_insert_text_float), NULL);
  gtk_grid_attach(GTK_GRID(grid), deposit, 1, 0, 2, 1);
  term_deposit = gtk_entry_new();
  gtk_entry_set_alignment(GTK_ENTRY(term_deposit), 1);
  gtk_entry_set_max_length(GTK_ENTRY(term_deposit), 255);
  g_signal_connect(G_OBJECT(term_deposit), "insert-text", G_CALLBACK(on_insert_text_int), NULL);
  gtk_grid_attach(GTK_GRID(grid), term_deposit, 1, 1, 2, 1);
  percent_rate_deposit = gtk_entry_new();
  gtk_entry_set_alignment(GTK_ENTRY(percent_credit), 1);
  gtk_entry_set_max_length(GTK_ENTRY(percent_credit), 255);
  g_signal_connect(G_OBJECT(percent_credit), "insert-text", G_CALLBACK(on_insert_text_float), NULL);
  gtk_grid_attach(GTK_GRID(grid), percent_credit, 1, 2, 2, 1);
}

void on_deposit_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window_new = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window_new), "Deposit calculator");
    gtk_window_set_default_size(GTK_WINDOW(window_new), 400, 300);
    GtkWidget *box_new = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window_new), box_new);
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_box_pack_start(GTK_BOX(box_new), grid, TRUE, TRUE, 0);
    init_entries_deposit(grid);
    init_buttons_deposit(grid);
    gtk_widget_show_all(window_new);
}