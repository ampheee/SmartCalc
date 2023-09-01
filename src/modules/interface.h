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
    GtkWidget *entry;
    GtkWidget *x_entry;
} UserData;

void InitUserGui(GtkWidget *window);
void InitCreditCalc(GtkWidget *grid, GtkWidget *Entry);
void InitDepositCalc(GtkWidget *grid, GtkWidget *Entry);

#endif  //SMARTCALC_INTERFACE_H_