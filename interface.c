#include "interface.h"

void on_digit_button_clicked(GtkButton *button, gpointer user_data) {
    //todo get iter text
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
    g_free((gchar*)current_text);

}

void on_func_button_clicked(GtkButton *button, gpointer user_data) {
    const gchar *digit = gtk_button_get_label(button);
    GtkEntry *entry = GTK_ENTRY(user_data);
    const gchar *current_text = gtk_entry_get_text(entry);
    gchar *new_text = g_strconcat(current_text, digit, NULL);
    gtk_entry_set_text(entry, new_text);
    g_free(new_text);
}