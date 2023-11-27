#include <gtk/gtk.h>

int check_elem_interface(GObject *element, char *main_window_name); // Checking for the absence of an interface element

void run_interface_gtk_main(int argc, char *argv[])
{   // Run interface GTK (main interface)

    char main_window_name[] = "main_application_window";
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new();

    gtk_builder_add_from_file(builder, "../interface/interface_ru.glade", NULL);

    // Get a pointer to the top level of the window
    GObject *window = gtk_builder_get_object(builder, main_window_name);

    check_elem_interface(window, &main_window_name);

    // Convert GObject to GtkWidget
    GtkWidget *main_window = GTK_WIDGET(window);

    // Connect the window closing signal to the gtk_main_quit function
    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Display the window
    gtk_widget_show_all(main_window);

    // Start the GTK event loop
    gtk_main();
}


int check_elem_interface(GObject *element, char *window_name)
{   // Checking for the absence of an interface element

    if (element == NULL) {
        g_error(
            "The '%s' object could not be found in the interface file.",
            window_name
        );
        return 1;
    }
}

// Получите указатель на GtkTextView
    //GtkWidget *text_view = GTK_WIDGET(gtk_builder_get_object(builder, "your_text_view_name"));

    // Получите буфер текста
    //GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Создайте установщик стилей и установите нужный шрифт
    //PangoFontDescription *font_desc = pango_font_description_from_string("Serif 12");
    //gtk_widget_override_font(text_view, font_desc);
    //pango_font_description_free(font_desc);

    // Другие операции по инициализации вашего приложения...
