#include <gtk/gtk.h>

#include "structures.h"
#include "util.h"

#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED


// Output the 10 last iterations
void last_ten_iter(GtkWidget *widget,  TObject *text_struct);

// Output the last iteration
void last_iter(GtkWidget *widget,  TObject *text_struct);

// Download to DB
void download_db(GtkWidget *widget,  TObject *text_struct);

// Delete DB
void delete_db(GtkWidget *widget, TObject *text_struct);

// Create DB
void create_db(GtkWidget *widget, TObject *text_struct);

#endif // DB_H_INCLUDED
