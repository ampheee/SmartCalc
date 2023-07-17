#include "calculator.h"

#define UNUSED(expr) (void)(expr)
// Функция-обработчик для кнопок-цифр
int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "SmartCalc");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Создание вертикального контейнера
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    // Создание текстового поля
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);
    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 0);
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
    const gchar *digits[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+",
    };
    int row, col, i = 0;
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            GtkWidget *button = gtk_button_new_with_label(digits[i]);
            gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
            if (i < 14) {
                g_signal_connect(button, "clicked", G_CALLBACK(on_digit_button_clicked), entry);
            } else if (i == 14) {
                g_signal_connect(button, "clicked", G_CALLBACK(on_equal_button_clicked), entry);
            } else {
                g_signal_connect(button, "clicked", G_CALLBACK(on_clear_button_clicked), entry);
            }
            i++;
        }
    }
    gtk_widget_show_all(window);
    gtk_main();
}
    