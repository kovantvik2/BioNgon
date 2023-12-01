#include <stdio.h>
#include <gtk/gtk.h>
#include "structures.h"

int check_elem_interface(GObject *element, char *element_name)
{   // Checking for the absence of an interface element

    if (element == NULL) {
        g_error(
            "The '%s' object could not be found in the interface file.",
            element_name
        );
        return 1;
    }
    return 0;
}

void exit_the_program(GtkWidget *main_window)
{   // Exit the program

    gtk_main_quit();
}

void open_file(GtkWidget *widget, TObject *text_struct)
{   // Open the data file

    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new(
        "Open File", GTK_WINDOW(gtk_widget_get_toplevel(widget)),
        action,
        "Open",
        GTK_RESPONSE_ACCEPT,
        "Cancel",
        GTK_RESPONSE_CANCEL,
        NULL
    );

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        text_struct->filename = g_strdup(
            gtk_file_chooser_get_filename(chooser)
        );
        if (text_struct->filename == NULL) {
            g_error("File selection error - '%s'\n", text_struct->filename);
            return 1;
        }
    }
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(
        GTK_TEXT_VIEW(text_struct->text_field)
    );
    gtk_text_buffer_set_text(buffer, "", -1);
    gtk_text_buffer_insert_at_cursor(buffer, "Selected File:\n", -1);
    gtk_text_buffer_insert_at_cursor(buffer, text_struct->filename, -1);
    gtk_widget_destroy(dialog);
}

