#ifndef _GRAPH_CALLBACKS_
#define _GRAPH_CALLBACKS_

#include <gtk-3.0/gtk/gtk.h>
#include <math.h>

#include "queue.h"
#include "parse.h"
#include "arithmetics.h"

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

#define WIDTH 600
#define HEIGHT 600
#define ROTATE 1
#define DONT_ROTATE 0


void draw_graph_line(s_graph_properties *gp);
void draw_axis_text(s_graph_properties *gp, gdouble value, int rotate);
void draw_axis(s_graph_properties *gp);
gboolean on_draw(GtkWidget *widget, cairo_t *cairo);
void button_draw_clicked(GtkWidget *button, gpointer entry);
void close_window(GtkWidget *widget, gpointer window);
void check_same_dom_codom_toggled_cb(GtkCheckButton *button);
void check_same_max_min_toggled_cb(GtkCheckButton *button);
int init_graph(const char *input);

#endif //_GRAPH_CALLBACKS