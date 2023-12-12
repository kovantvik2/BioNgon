#include <gtk/gtk.h>

#include "structures.h"
#include "sqlite3.h"

#define NUMBER_OF_NUCLEOTIDES 5


int get_total_records(const char *table_name, const char *db_path); // Are there any rows in the table
void exit_the_window(GtkWidget *menu_item, gpointer user_data); // Exit the window
void init_struct(TObject *text_struct); // Basic initialization of the structure
void error_message(char *error); // Displays an error window
int check_elem_interface(GObject *element, char *element_name); // Checking for the absence of an interface element


void exit_the_window(GtkWidget *menu_item, gpointer user_data)
{   // Exit the window

    GtkWidget *window = GTK_WIDGET(user_data);
    gtk_widget_destroy(window);
}


void init_struct(TObject *text_struct)
{   // Basic initialization of the structure

    text_struct->path_to_db = "../DB/DB.db";
    text_struct->length_dna = 0;
    text_struct->length_ATGCU = 0;
    text_struct->gc_content = 0;
    text_struct->gc_content_percent = 0.0;
    int initial_values[NUMBER_OF_NUCLEOTIDES] = {65, 85, 71, 67, 84};
    for (int i = 0; i < NUMBER_OF_NUCLEOTIDES; i++) {
        text_struct->array_of_nucleotides[i] = initial_values[i];
        text_struct->array_number_of_nucleotides[i] = 0;
        text_struct->array_percent_of_nucleotides[i] = 0.0;
    }
}


void error_message(char *error)
{   // Displays an error window

    GtkBuilder *second_builder = gtk_builder_new();
    gtk_builder_add_from_file(second_builder, "../interface/interface_en.glade", NULL);

    // Processing the second window call
    char second_window_name[] = "second_application_window";
    GObject *second_window_object = gtk_builder_get_object(
        second_builder, second_window_name
    );
    check_elem_interface(second_window_object, &second_window_name);
    GtkWidget *second_window = GTK_WIDGET(second_window_object);

    char second_window_title[] = "Service message";
    gtk_window_set_title(GTK_WINDOW(second_window), second_window_title);

    g_signal_connect(second_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(second_window);

    // Error output in the label field
    char error_label_name[] = "first_gtk_label_second_main";
    GObject *error_label_object = (
        gtk_builder_get_object(second_builder, error_label_name)
    );
    check_elem_interface(
        error_label_object,
        &error_label_name
    );
    GtkWidget *error_label = GTK_WIDGET(error_label_object);
    gtk_label_set_text(GTK_LABEL(error_label), error);

    // Processing of pressing the exit button from the program
    char button_exit_the_program_name[] = "first_gtk_button_second_window";
    GObject *button_object_exit_the_program = (
        gtk_builder_get_object(second_builder, button_exit_the_program_name)
    );
    check_elem_interface(
        button_object_exit_the_program,
        &button_exit_the_program_name
    );
    GtkWidget *button_exit_the_program = GTK_WIDGET(
        button_object_exit_the_program
    );
    g_signal_connect(
        button_exit_the_program, "clicked",
        G_CALLBACK(exit_the_window), second_window
    );

    gtk_main();
}


int check_elem_interface(GObject *element, char *element_name)
{   // Checking for the absence of an interface element

    if (element == NULL) {
        g_error(
            "The '%s' object could not be "
            "found in the interface file.",
            element_name
        );
        return 1;
    }
    return 0;
}

int get_total_records(const char *table_name, const char *db_path)
{   // Are there any rows in the table

    sqlite3 *db;
    if (sqlite3_open(db_path, &db) != SQLITE_OK) {
        char db_error[256];
        snprintf(
            db_error, sizeof(db_error),
            "Error: \n%s",
            sqlite3_errmsg(db)
        );
        sqlite3_close(db);
        return;
    }

    char sql[512];
    snprintf(
        sql, sizeof(sql),
        "SELECT COUNT(*) FROM %s", table_name
    );

    int total_records = -1;
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            total_records = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return total_records;
}

