#include "calculator.h"

void on_digit_button_clicked(GtkButton *button, gpointer user_data) {
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
    const gchar *current_text = gtk_entry_get_text(entry);
    gchar *text_ptr = (gchar *) current_text;
    unsigned char *res = (unsigned char *) calloc(1, 100);
    unsigned char *res_start = res;
    ERROR err = parse_num_string(&res, &text_ptr);
    gchar *result = g_strdup_printf("error");
    if (!err){
        result = g_strdup_printf("%s+5",  res_start);
        free(res_start);
    }
    gtk_entry_set_text(entry, result);
    g_free(result);
}