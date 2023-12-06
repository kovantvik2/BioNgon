#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "util.h"
#include "sqlite3.h"


gboolean create_db_callback(gpointer user_data)
{

    TObject *text_struct_c = (TObject *)user_data;
    sqlite3 *db;
    int rc = sqlite3_open(
        text_struct_c->path_to_db, &db
    );

    if (rc != SQLITE_OK) {
        char db_error[256];
        snprintf(
            db_error, sizeof(db_error),
            "Cannot create database: \n%s",
            sqlite3_errmsg(db)
        );
        error_message(&db_error);
    }
    else {
        char create_db_mess[] = "The database has been created";
        error_message(&create_db_mess);
    }

    sqlite3_close(db);

    return G_SOURCE_REMOVE;
}

void create_db(GtkWidget *widget, TObject *text_struct)
{   // Create DB


    if (access(text_struct->path_to_db, F_OK) != -1) {
        char db_error_alr[] = "The database already exists";
        error_message(&db_error_alr);
    }
    else {
        g_idle_add(create_db_callback, text_struct);
    }
;
}
