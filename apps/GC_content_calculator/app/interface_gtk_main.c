#include <stdio.h>
#include <gtk/gtk.h>

// Checking for the absence of an interface element
int check_elem_interface(GObject *element, char *element_name);

// Exit the program
void exit_the_program(GtkWidget *main_window);

// Open the data file
void open_file(GtkWidget *widget, char **filename);


void run_interface_gtk_main(int argc, char *argv[], char *filename)
{   // Run interface GTK (main interface)

    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../interface/interface_ru.glade", NULL);

    // Processing the main window call
    char main_window_name[] = "main_application_window";
    GObject *window = gtk_builder_get_object(builder, main_window_name);
    check_elem_interface(window, &main_window_name);
    GtkWidget *main_window = GTK_WIDGET(window);
    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(main_window);

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
        G_CALLBACK(exit_the_program), main_window
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
        G_CALLBACK(open_file), filename
    );

    // Start the GTK event loop
    gtk_main();
}


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


void open_file(GtkWidget *widget, char **filename)
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
        *filename = g_strdup(gtk_file_chooser_get_filename(chooser));
        if (filename == NULL) {
            g_error("Error opening file '%s'\n", *filename);
            return 1;
        }
    }
    gtk_widget_destroy(dialog);

}

