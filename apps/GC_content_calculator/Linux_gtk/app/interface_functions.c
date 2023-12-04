#include <stdio.h>
#include <gtk/gtk.h>
#include "structures.h"


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
        gtk_text_buffer_insert_at_cursor(
            buffer, "The path to the selected file:\n", -1
        );
        gtk_text_buffer_insert_at_cursor(
            buffer, text_struct->filename, -1
        );
    }
    gtk_widget_destroy(dialog);
}

void save_file(GtkWidget *widget, TObject *text_struct)
{   // Save file

    if (text_struct->check_txt_field == 1) {
        GtkWidget *dialog;
        GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
        gint res;

        dialog = gtk_file_chooser_dialog_new(
            "Save File", GTK_WINDOW(gtk_widget_get_toplevel(widget)),
            action,
            "Save",
            GTK_RESPONSE_ACCEPT,
            "Cancel",
            GTK_RESPONSE_CANCEL,
            NULL
        );

        res = gtk_dialog_run(GTK_DIALOG(dialog));

        if (res == GTK_RESPONSE_ACCEPT) {
            text_struct->filename_save_as = gtk_file_chooser_get_filename(
                GTK_FILE_CHOOSER(dialog)
            );
        }

        if (text_struct->filename_save_as != NULL) {
            text_struct->file_write_data = fopen(
                text_struct->filename_save_as, "w+t"
            );
            if (text_struct->file_write_data != NULL) {
                GtkTextBuffer *buffer = gtk_text_view_get_buffer(
                    GTK_TEXT_VIEW(text_struct->text_field)
                );
                GtkTextIter start, end;
                gtk_text_buffer_get_start_iter(buffer, &start);
                gtk_text_buffer_get_end_iter(buffer, &end);

                char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
                fprintf(text_struct->file_write_data, text);
            }
            fclose(text_struct->file_write_data);
        }
        gtk_widget_destroy(dialog);
    }
    else if (text_struct->check_txt_field == 0) {
        char error_read_file[] = "The file has not been read.\n"
                                 "There is nothing to save.";
        error_message(&error_read_file);
    }
}

