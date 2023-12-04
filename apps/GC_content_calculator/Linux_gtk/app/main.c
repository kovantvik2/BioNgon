#include <stdio.h>
#include <stdlib.h>
#include "interface_functions.h"
#include "nucleotide_functions.h"
#include "structures.h"
#include "util.h"


int main(int argc, char *argv[])
{
    TObject text_struct;
    init_struct(&text_struct);
    text_struct.check_txt_field = 0;

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

    //
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

    // Start the GTK event loop
    gtk_main();

    return 0;
}
