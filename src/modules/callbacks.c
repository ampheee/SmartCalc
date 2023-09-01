#include "callbacks.h"
#include "../bonus/credit/credit.h"

#define UNUSED(x) (void)(x)

void on_insert_text_float(GtkEditable *editable, const gchar *text, gint length) {
    for (int i = 0; i < length; i++) {
        if (!g_ascii_isdigit(text[i]) && text[i] != '.') {
            g_signal_stop_emission_by_name(editable, "insert-text");
            return;
        }
    }
}

void on_insert_text_int(GtkEditable *editable, const gchar *text, gint length) {
    for (int i = 0; i < length; i++) {
        if (!g_ascii_isdigit(text[i])) {
            g_signal_stop_emission_by_name(editable, "insert-text");
            return;
        }
    }
}

double convert_entry_to_num(GtkWidget *entry) {
    size_t nums = 0;
    const gchar *str = gtk_entry_get_text(GTK_ENTRY(entry));
    char *buffer = (char *) calloc (strlen(str) + 1, sizeof(gchar));
    char *temp = buffer;
    snprintf(buffer, sizeof(str), "%s", str);
    double num = parse_to_float(&buffer, &nums);
    free(temp);
    return num;
}

void on_digit_func_button_clicked(GtkButton *button, gpointer user_data) {
    const gchar *digit = gtk_button_get_label(button);
    GtkEntry *entry = GTK_ENTRY(user_data);
    const gchar *current_text = gtk_entry_get_text(entry);
    gchar *new_text = g_strconcat(current_text, digit, NULL);
    gtk_entry_set_text(entry, new_text);
    g_free(new_text); 
}

void on_clear_button_clicked(GtkButton *button, gpointer user_data) {
    UNUSED(button);
    GtkEntry *entry = GTK_ENTRY(user_data);
    gtk_entry_set_text(entry, "");
}

void on_equal_button_clicked(GtkButton *button, gpointer user_data) {
    UNUSED(button);
    gchar input[256] = {0};
    UserData *data = (UserData *) user_data;
    GtkEntry *entry = GTK_ENTRY(data->entry);
    GtkEntry *x_entry = GTK_ENTRY(data->x_entry);
    const gchar *current_text = gtk_entry_get_text(entry);
    const gchar *x_entry_text = gtk_entry_get_text(x_entry);
    if (strlen(x_entry_text) > 0) {
        char *temp_str = replace_word((char *) current_text, "x", x_entry_text);
        snprintf(input, sizeof(input), "%s", temp_str);
        free(temp_str);
    } else {
        snprintf(input, sizeof(input), "%s", current_text);
    }
    Queue *res_que = queue_init();
    if (str_to_polish(input, &res_que) == SUCCESS) {
        int Status = SUCCESS;
        double result = calculate(res_que, &Status);
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
  g_signal_connect(window_new, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
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
    g_signal_connect(window_new, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
}

void on_graph_button_clicked(GtkWidget *button, gpointer user_data) {
    UNUSED (button);
    UserData *data = (UserData *) user_data;
    GtkEntry *entry = GTK_ENTRY(data->entry);
    const gchar *current_text = gtk_entry_get_text(entry);
    init_graph(current_text);
}

void setup_entry(GtkWidget *entry) {
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);
    gtk_entry_set_max_length(GTK_ENTRY(entry), 255);
}

void setup_credentials(GtkWidget *grid, int col, int row,
                        int width, int heigth) {
    GtkWidget *credentials_button = gtk_button_new_with_label("powered by babbling\n\tschool21 | 2023");
    gtk_grid_attach(GTK_GRID(grid), credentials_button, col, row, width, heigth);
    gtk_widget_set_sensitive(credentials_button, FALSE);
}

void connect_entry(GtkWidget *grid, GtkWidget *entry, int col, int row, 
                            int width, int heigth,  gboolean parse_int) {
    setup_entry(entry);
    if (parse_int) {
      g_signal_connect(G_OBJECT(entry), "insert-text", G_CALLBACK(on_insert_text_int), NULL);
    } else {
      g_signal_connect(G_OBJECT(entry), "insert-text", G_CALLBACK(on_insert_text_float), NULL);
    }
    gtk_grid_attach(GTK_GRID(grid), entry, col, row, width, heigth);
}
