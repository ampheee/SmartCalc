#include "calculator.h"

// Функция вычисления математического выражения
int eval_expression(const gchar *expression) {
    return 0;
}


// Функция-обработчик для кнопок-цифр
void on_digit_button_clicked(GtkButton *button, gpointer user_data) {
    // Получаем текст с кнопки
    const gchar *digit = gtk_button_get_label(button);
    // Получаем указатель на текстовое поле
    GtkEntry *entry = GTK_ENTRY(user_data);
    // Получаем текущий текст из текстового поля
    const gchar *current_text = gtk_entry_get_text(entry);
    // Соединяем текущий текст с нажатой цифрой
    gchar *new_text = g_strconcat(current_text, digit, NULL);
    // Устанавливаем новый текст в текстовое поле
    gtk_entry_set_text(entry, new_text);
    // Освобождаем память
    g_free(new_text);
}

// Функция-обработчик для кнопки "С"
void on_clear_button_clicked(GtkButton *button, gpointer user_data) {
    // Получаем указатель на текстовое поле
    GtkEntry *entry = GTK_ENTRY(user_data);
    // Очищаем текстовое поле
    gtk_entry_set_text(entry, "");
}

// Функция-обработчик для кнопки "="
void on_equal_button_clicked(GtkButton *button, gpointer user_data) {
    // Получаем указатель на текстовое поле
    GtkEntry *entry = GTK_ENTRY(user_data);
    // Получаем текущий текст из текстового поля
    const gchar *current_text = gtk_entry_get_text(entry);
    // Вычисляем результат
    gchar *result = g_strdup_printf("%d", eval_expression(current_text));
    // Устанавливаем результат в текстовое поле
    gtk_entry_set_text(entry, result);
    // Освобождаем память
    g_free(result);
}


// Главная функция
int main(int argc, char **argv) {
    // Инициализация GTK+
    gtk_init(&argc, &argv);
    // Создание главного окна
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "SmartCalc");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Создание вертикального контейнера
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // Создание текстового поля
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);
    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 0);

    // Создание таблицы для кнопок
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
    
    // Массив для цифр
    const gchar *digits[] = {"7", "8", "9", "/",
                             "4", "5", "6", "*",
                             "1", "2", "3", "-",
                             "0", ".", "=", "+"};
    
    int row, col, i = 0;
    
    // Создание кнопок
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            GtkWidget *button = gtk_button_new_with_label(digits[i]);
            gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
            // Подключение обработчиков событий к кнопкам
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
    