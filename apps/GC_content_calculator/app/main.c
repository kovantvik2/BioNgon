#include <stdio.h>
#include <stdlib.h>
#include "interface_functions.h"
#include "nucleotide_functions.h"
#include "structures.h"

#define BUFFER_SIZE 8192 // BufferBuffer size




int main(int argc, char *argv[])
{
    long int length_dna = 0;
    long int length_ATGCU = 0;
    long int gc_content = 0;
    float gc_content_percent = 0.0;
    int array_of_nucleotides[NUMBER_OF_NUCLEOTIDES] = {65, 85, 71, 67, 84}; // ASCII codes 'A', 'U', 'G', 'C', 'T'
    long int array_number_of_nucleotides[NUMBER_OF_NUCLEOTIDES] = {0, 0, 0, 0, 0};
    float array_percent_of_nucleotides[NUMBER_OF_NUCLEOTIDES] = {0.0, 0.0, 0.0, 0.0, 0.0};
    TObject text_struct;

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
        G_CALLBACK(exit_the_program), main_window
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
        button_run, "activate",
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

    if (text_struct.file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    /*else {
        char buffer[BUFFER_SIZE];
        size_t bytesRead;

        count_dna(
            &buffer, &bytesRead, &text_struct,
            &length_dna, &length_ATGCU,
            &array_number_of_nucleotides,
            &array_of_nucleotides
        );

        percent_nucl(
            &array_percent_of_nucleotides,
            &array_number_of_nucleotides,
            &length_dna
        );

        for (int i = 0; i < NUMBER_OF_NUCLEOTIDES; i++) {
            if (array_number_of_nucleotides[i] > 0) {
                printf("%c - %ld - %0.2f%\n",
                    (char) array_of_nucleotides[i],
                    array_number_of_nucleotides[i],
                    array_percent_of_nucleotides[i]
                );
            }
        }

        gc_percent(
            &array_number_of_nucleotides,
            &gc_content_percent, &length_dna,
            &gc_content
        );

        printf("Total number of characters - %ld\n", length_dna);
        printf("Number of ATGCU - %ld\n", length_ATGCU);
        printf("Other characters - %ld\n", length_dna - length_ATGCU);
        printf("Number of GC content in characters - %ld\n", gc_content);
        printf("Number of GC content in percent - %0.2f%\n", gc_content_percent);
    }*/



    // Start the GTK event loop
    gtk_main();





    /*for (int i = 0; i < NUMBER_OF_NUCLEOTIDES; i++) {
        if (array_number_of_nucleotides[i] > 0) {
            fprintf(output, "%c %ld %0.2f\n", (char) array_of_nucleotides[i], \
                    array_number_of_nucleotides[i], array_percent_of_nucleotides[i]);
        }
    } */


    return 0;
}
