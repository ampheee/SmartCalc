#ifndef SMARTCALC_INTERFACE_H_
#define SMARTCALC_INTERFACE_H_

// #include <cairo.h>
// #include <pango/pangocairo.h>

#include "calculator.h"
#include "queue.h"
#include "stack.h"
#include "callbacks.h"
#include <locale.h>

typedef struct {
  cairo_t *cr;
  gdouble min_x;
  gdouble max_x;
  gdouble min_y;
  gdouble max_y;
  gdouble dx;
  gdouble dy;
  gdouble right_limit;
  gdouble left_limit;
  gdouble lower_limit;
  gdouble upper_limit;
} s_graph_properties;

#define DA_WIDTH 400
#define DA_HEIGHT 400
#define ROTATE 1
#define DONT_ROTATE 0

void InitUserGui(GtkWidget *window);
void InitCreditCalc(GtkWidget *grid, GtkWidget *Entry);
void InitDepositCalc(GtkWidget *grid, GtkWidget *Entry);

void draw_graph_line(s_graph_properties *gp);
void draw_axis_text(s_graph_properties *gp, gdouble value, int rotate);
void draw_axis(s_graph_properties *gp);
gboolean on_draw(GtkWidget *widget, cairo_t *cairo);
void button_draw_clicked(GtkWidget *button, gpointer entry);
void close_window(GtkWidget *widget, gpointer window);
void check_same_dom_codom_toggled_cb(GtkCheckButton *button);
void check_same_max_min_toggled_cb(GtkCheckButton *button);
int graph_output(char *input);

#endif  //SMARTCALC_INTERFACE_H_