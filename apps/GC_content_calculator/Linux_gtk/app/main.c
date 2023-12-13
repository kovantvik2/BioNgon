#include <stdio.h>
#include <stdlib.h>

#include "interface_functions.h"
#include "nucleotide_functions.h"
#include "sqlite3.h"
#include "structures.h"
#include "util.h"
#include "DB.h"


int main(int argc, char *argv[])
{
    TObject text_struct;
    init_struct(&text_struct);

    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../interface/interface_en.glade", NULL);

    // Processing the main window call
    char main_window_name[] = "main_application_window";
    GObject *window = gtk_builder_get_object(
        builder, main_window_name
    );
    check_elem_interface(window, &main_window_name);
    GtkWidget *main_window = GTK_WIDGET(window);

    char main_window_title[] = "GC Content Calculator";
    gtk_window_set_title(GTK_WINDOW(main_window), main_window_title);

    g_signal_connect(
        main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL
    );
    gtk_widget_show_all(main_window);

    char text_field_name[] = "first_gtk_text_view_main_window";
    GObject *text_field_object = (
        gtk_builder_get_object(builder, text_field_name)
    );
    check_elem_interface(
        text_field_object,
        &text_field_name
    );
    text_struct.text_field = GTK_WIDGET(text_field_object);

    // Processing of pressing the exit button from the program
    char button_exit_the_program_name[] = "third_gtk_button_main_window";
    GObject *button_object_exit_the_program = (
        gtk_builder_get_object(builder, button_exit_the_program_name)
    );
    check_elem_interface(
        button_object_exit_the_program,
        &button_exit_the_program_name
    );
    GtkWidget *button_exit_the_program = GTK_WIDGET(button_object_exit_the_program);
    g_signal_connect(
        button_exit_the_program, "clicked",
        G_CALLBACK(exit_the_window), main_window
    );

    // Start counting
    char button_run_name[] = "first_gtk_button_main_window";
    GObject *button_run_object = (
        gtk_builder_get_object(builder, button_run_name)
    );
    check_elem_interface(
        button_run_object,
        &button_run_name
    );
    GtkWidget *button_run = GTK_WIDGET(button_run_object);
    g_signal_connect(
        button_run, "clicked",
        G_CALLBACK(read_file), &text_struct
    );

    // File Opening Processing
    char button_menu_open_file_name[] = "first_gtk_image_menu_item_file";
    GObject *button_menu_object_open_file = (
        gtk_builder_get_object(builder, button_menu_open_file_name)
    );
    check_elem_interface(
        button_menu_object_open_file,
        &button_menu_open_file_name
    );
    GtkWidget *button_menu_open_file = GTK_WIDGET(button_menu_object_open_file);
    g_signal_connect(
        button_menu_open_file, "activate",
        G_CALLBACK(open_file), &text_struct
    );

    // Save file
    char button_menu_save_file_name[] = "third_gtk_image_menu_item_file";
    GObject *button_menu_object_save_file = (
        gtk_builder_get_object(builder, button_menu_save_file_name)
    );
    check_elem_interface(
        button_menu_object_save_file,
        &button_menu_save_file_name
    );
    GtkWidget *button_menu_save_file = GTK_WIDGET(button_menu_object_save_file);
    g_signal_connect(
        button_menu_save_file, "activate",
        G_CALLBACK(save_file), &text_struct
    );

    // Exit program
    char button_menu_exit_name[] = "fourth_gtk_image_menu_item_file";
    GObject *button_menu_exit_object = (
        gtk_builder_get_object(builder, button_menu_exit_name)
    );
    check_elem_interface(
        button_menu_exit_object,
        &button_menu_exit_name
    );
    GtkWidget *button_menu_exit = GTK_WIDGET(button_menu_exit_object);
    g_signal_connect(
        button_menu_exit, "activate",
        G_CALLBACK(exit_the_window), main_window
    );

    // Create DB
    char button_menu_create_db_name[] = "first_gtk_image_menu_db_file";
    GObject *button_menu_create_db_object = (
        gtk_builder_get_object(builder, button_menu_create_db_name)
    );
    check_elem_interface(
        button_menu_create_db_object,
        &button_menu_create_db_name
    );
    GtkWidget *button_menu_create_db = GTK_WIDGET(button_menu_create_db_object);
    g_signal_connect(
        button_menu_create_db, "activate",
        G_CALLBACK(create_db), &text_struct
    );

    // Delete DB
    char button_menu_delete_db_name[] = "second_gtk_image_menu_db_file";
    GObject *button_menu_delete_db_object = (
        gtk_builder_get_object(builder, button_menu_delete_db_name)
    );
    check_elem_interface(
        button_menu_delete_db_object,
        &button_menu_delete_db_name
    );
    GtkWidget *button_menu_delete_db = GTK_WIDGET(button_menu_delete_db_object);
    g_signal_connect(
        button_menu_delete_db, "activate",
        G_CALLBACK(delete_db), &text_struct
    );

    // Download to DB
    char button_download_name[] = "second_gtk_button_main_window";
    GObject *button_download_object = (
        gtk_builder_get_object(builder, button_download_name)
    );
    check_elem_interface(
        button_download_object,
        &button_download_name
    );
    GtkWidget *button_download = GTK_WIDGET(button_download_object);
    g_signal_connect(
        button_download, "clicked",
        G_CALLBACK(download_db),  &text_struct
    );

    // Output the last iteration
    char button_last_iter_name[] = "fourth_gtk_image_menu_db_file";
    GObject *button_last_iter_object = (
        gtk_builder_get_object(builder, button_last_iter_name)
    );
    check_elem_interface(
        button_last_iter_object,
        &button_last_iter_name
    );
    GtkWidget *button_last_iter = GTK_WIDGET(button_last_iter_object);
    g_signal_connect(
        button_last_iter, "activate",
        G_CALLBACK(last_iter),  &text_struct
    );

    // Output the 10 last iterations
    char button_ten_last_iter_name[] = "fifth_gtk_image_menu_db_file";
    GObject *button_ten_last_iter_object = (
        gtk_builder_get_object(builder, button_ten_last_iter_name)
    );
    check_elem_interface(
        button_ten_last_iter_object,
        &button_ten_last_iter_name
    );
    GtkWidget *button_ten_last_iter = GTK_WIDGET(button_ten_last_iter_object);
    g_signal_connect(
        button_ten_last_iter, "activate",
        G_CALLBACK(last_ten_iter),  &text_struct
    );

    // To clear the text field
    char button_menu_clear_name[] = "fifth_gtk_image_menu_item_file";
    GObject *button_menu_clear_object = (
        gtk_builder_get_object(builder, button_menu_clear_name)
    );
    check_elem_interface(
        button_menu_clear_object,
        &button_menu_clear_name
    );
    GtkWidget *button_menu_clear = GTK_WIDGET(button_menu_clear_object);
    g_signal_connect(
        button_menu_clear, "activate",
        G_CALLBACK(clear_text_field),  &text_struct
    );

    // Uploading the database to csv
    char button_menu_upload_name[] = "sixth_gtk_image_menu_db_file";
    GObject *button_menu_upload_object = (
        gtk_builder_get_object(builder, button_menu_upload_name)
    );
    check_elem_interface(
        button_menu_upload_object,
        &button_menu_upload_name
    );
    GtkWidget *button_menu_upload = GTK_WIDGET(button_menu_upload_object);
    g_signal_connect(
        button_menu_upload, "activate",
        G_CALLBACK(uploading_database), &text_struct
    );

    // Delete last iteration
    char button_menu_del_last_iter_name[] = "seventh_gtk_image_menu_db_file";
    GObject *button_menu_del_last_iter_object = (
        gtk_builder_get_object(builder, button_menu_del_last_iter_name)
    );
    check_elem_interface(
        button_menu_del_last_iter_object,
        &button_menu_del_last_iter_name
    );
    GtkWidget *button_menu_del_last_iter = GTK_WIDGET(button_menu_del_last_iter_object);
    g_signal_connect(
        button_menu_del_last_iter, "activate",
        G_CALLBACK(delete_last_iteration), &text_struct
    );


    // Start the GTK event loop
    gtk_main();
    return 0;
}
