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
    }
    if (text_struct->filename != NULL) {
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(
            GTK_TEXT_VIEW(text_struct->text_field)
        );
        gtk_text_buffer_set_text(buffer, "", -1);
        gtk_text_buffer_insert_at_cursor(buffer, "Selected File:\n", -1);
        gtk_text_buffer_insert_at_cursor(buffer, text_struct->filename, -1);
    }
    gtk_widget_destroy(dialog);
}

void save_as_file(GtkWidget *widget, TObject *text_struct)
{   // Save as

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_struct->text_field));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    gtk_text_buffer_set_text(buffer, "", -1);
    gtk_text_buffer_insert_at_cursor(buffer, text, -1);
    if (text != NULL) {
        GtkWidget *dialog;
        GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
        gint res;

        dialog = gtk_file_chooser_dialog_new(
            "Save File", GTK_WINDOW(gtk_widget_get_toplevel(widget)),
            action,
            "Save as",
            GTK_RESPONSE_ACCEPT,
            "Cancel",
            GTK_RESPONSE_CANCEL,
            NULL
        );

        res = gtk_dialog_run(GTK_DIALOG(dialog));

        if (res == GTK_RESPONSE_ACCEPT) {
            text_struct->filename_save_as = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        }
        text_struct->file_write_data = fopen(text_struct->filename_save_as, "w");

        for (int i = 0; i < NUMBER_OF_NUCLEOTIDES; i++) {
            if (text_struct->array_number_of_nucleotides[i] > 0) {
                fprintf(text_struct->file_write_data, "%c %ld %0.2f\n", (char)text_struct->array_of_nucleotides[i], \
                    text_struct->array_number_of_nucleotides[i], text_struct->array_percent_of_nucleotides[i]);
            }
        }
        fclose(text_struct->file_write_data);
        gtk_widget_destroy(dialog);
    }
    else if (text == NULL) {
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_struct->text_field));
        gtk_text_buffer_set_text(
            buffer, (
                "No file is selected.\n"
                "Select and open the file, \n"
                "then click this button and the result \n"
                "will be displayed in this text field."
            ),
        -1);
        gtk_text_buffer_insert_at_cursor(buffer, "", -1);
    }
}

