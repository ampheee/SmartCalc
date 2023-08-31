#include "interface.h"

void InitUserGui(GtkWidget *window) {
    gtk_window_set_title(GTK_WINDOW(window), "SmartCalc");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), main_box);
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);
    gtk_entry_set_max_length(GTK_ENTRY(entry), 255);
    gtk_box_pack_start(GTK_BOX(main_box), entry, TRUE, TRUE, 0);
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_box_pack_start(GTK_BOX(main_box), grid, TRUE, TRUE, 0);
    const gchar *digits[] = {
        "7", "8", "9", "/", "log()", "sin()", "asin()",
        "4", "5", "6", "*", "ln()", "cos()", "acos()",
        "1", "2", "3", "-", "sqrt()", "tg()", "arctg()",
        "0", ".", "e", "+", "", "", ""
    };
    int row, col, i = 0;
    GtkWidget *equal_button = gtk_button_new_with_label((const gchar *)"=");
    gtk_grid_attach(GTK_GRID(grid), equal_button, 5, 4, 2, 1);
    g_signal_connect(equal_button, "clicked", G_CALLBACK(on_equal_button_clicked), entry);
    GtkWidget *clear_button = gtk_button_new_with_label((const gchar *)"C");
    gtk_grid_attach(GTK_GRID(grid), clear_button, 4, 4, 1, 1);
    g_signal_connect(clear_button, "clicked", G_CALLBACK(on_clear_button_clicked), entry);
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 7; col++) {
            if (row == 3 && col == 5) {
                GtkWidget *new_entry = gtk_entry_new();
                gtk_entry_set_alignment(GTK_ENTRY(new_entry), 1);
                gtk_entry_set_max_length(GTK_ENTRY(new_entry), 255);
                gtk_grid_attach(GTK_GRID(grid), new_entry, col, row, 2, 1);
            } else if (!(row == 3 && col > 3)){
                GtkWidget *button = gtk_button_new_with_label(digits[i]);
                gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
                g_signal_connect(button, "clicked", G_CALLBACK(on_digit_func_button_clicked), entry);
                row == 3 && col == 4 ? gtk_widget_set_sensitive(button, FALSE) : 0;
                i++;
            } else if (row == 3 && col == 4) {
                GtkWidget *button = gtk_label_new("Enter x:");
                gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
            }
        }
    }
    GtkWidget *button_graph = gtk_button_new_with_label("Graph");
    gtk_grid_attach(GTK_GRID(grid), button_graph, 0, 4, 4, 1);
    // g_signal_connect(button_graph, "clicked", G_CALLBACK(graph_output), entry);
    InitCreditCalc(grid, entry);
    InitDepositCalc(grid, entry);
    GtkWidget *credentials_button = gtk_button_new_with_label("powered by babbling\n\tschool21 | 2023");
    gtk_grid_attach(GTK_GRID(grid), credentials_button, 4, 5, 3, 1);
    gtk_widget_set_sensitive(credentials_button, FALSE);
}

void InitCreditCalc(GtkWidget *grid, GtkWidget *entry) {
    GtkWidget *button_credit = gtk_button_new_with_label("Credit");
    gtk_grid_attach(GTK_GRID(grid), button_credit, 2, 5, 2, 1);
    g_signal_connect(button_credit, "clicked", G_CALLBACK(on_credit_button_clicked), (gpointer)entry);
}

void InitDepositCalc(GtkWidget *grid, GtkWidget *entry) {
    GtkWidget *button_deposit = gtk_button_new_with_label("Deposit");
    gtk_grid_attach(GTK_GRID(grid), button_deposit, 0, 5, 2, 1);
    g_signal_connect(button_deposit, "clicked", G_CALLBACK(on_deposit_button_clicked), entry);
}

// void InitGraph(GtkWidget *grid, GtkWidget *entry) {

// }
