#include "calculator.h"

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    // g_object_set (gtk_settings_get_default(), "gtk-theme-name", "win32", NULL);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    InitUserGui(window);
    gtk_widget_show_all(window);
    gtk_main();
    // g_clear_pointer(&window, gtk_widget_destroy); //test
}