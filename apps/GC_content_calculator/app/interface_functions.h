#include <gtk/gtk.h>
#include "structures.h"
#ifndef INTERFACE_GTK_H_INCLUDED
#define INTERFACE_GTK_H_INCLUDED

// Checking for the absence of an interface element
int check_elem_interface(GObject *element, char *element_name);

// Exit the program
void exit_the_program(GtkWidget *main_window);

// Open the data file
void open_file(GtkWidget *widget, TObject **text_struct);

#endif // INTERFACE_GTK_H_INCLUDED
