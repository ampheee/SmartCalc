#include "calculator.h"

void on_digit_button_clicked(GtkButton *button, gpointer user_data) {
    //todo move cursor to the position
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
    gchar input[256];
    gChar *current_text = gtk_entry_get_text(entry);
    g_print("%s\n", current_text);
    g_snprintf(input, sizeof(input), "%s", current_text);
    que* qu;
    if (str_to_polish(input, &qu)) {
        double result = calculate(qu, 0);
        gchar expression[256];
    }
}