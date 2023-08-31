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
    char *buffer = (char *) calloc (1, sizeof(gchar));
    const gchar *str = gtk_entry_get_text(GTK_ENTRY(entry));
    snprintf(buffer, sizeof(str), "%s", str);
    double num = parse_to_float(&buffer, &nums);
    // free(buffer);
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
    GtkEntry *entry = GTK_ENTRY(user_data);
    UNUSED(button);
    gchar input[256] = {0};
    const gchar *current_text = gtk_entry_get_text(entry);
    g_print("%s\n", current_text);
    snprintf(input, sizeof(input), "%s", current_text);
    Queue *res_que = queue_init();
    if (str_to_polish(input, &res_que) == SUCCESS) {
        int Status = SUCCESS;
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
