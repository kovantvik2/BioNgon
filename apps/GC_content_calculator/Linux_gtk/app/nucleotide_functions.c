#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "structures.h"
#include "util.h"


void gc_percent(TObject *text_struct);
void percent_nucl(TObject *text_struct);
void count_dna(TObject *text_struct);

void read_file(GtkWidget *widget, TObject *text_struct)
{   // Open selected file

    if (text_struct->filename != NULL) {
        text_struct->file = fopen(text_struct->filename, "r");
        count_dna(text_struct);

        percent_nucl(text_struct);
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(
            GTK_TEXT_VIEW(text_struct->text_field)
        );
        gtk_text_buffer_set_text(buffer, "", -1);

        for (int i = 0; i < NUMBER_OF_NUCLEOTIDES; i++) {
            if (text_struct->array_number_of_nucleotides[i] > 0) {
                gtk_text_buffer_insert_at_cursor(
                    buffer, g_strdup_printf(
                        "%c - %ld - %0.2f%\n",
                        (char)text_struct->array_of_nucleotides[i],
                        text_struct->array_number_of_nucleotides[i],
                        text_struct->array_percent_of_nucleotides[i]
                    ),
                -1);
            }
        }

        gc_percent(text_struct);


        gtk_text_buffer_insert_at_cursor(
            buffer, g_strdup_printf(
                "Total number of characters - %ld\n",
                text_struct->length_dna
            ), -1);
        gtk_text_buffer_insert_at_cursor(
            buffer, g_strdup_printf(
                "Number of ATGCU - %ld\n",
                text_struct->length_ATGCU
            ),
        -1);
        gtk_text_buffer_insert_at_cursor(
            buffer, g_strdup_printf(
                "Other characters - %ld\n",
                text_struct->length_dna
                - text_struct->length_ATGCU
            ),
        -1);
        gtk_text_buffer_insert_at_cursor(
            buffer, g_strdup_printf(
                "Number of GC content in characters - %ld\n",
                text_struct->gc_content
            ),
        -1);
        gtk_text_buffer_insert_at_cursor(
            buffer, g_strdup_printf(
                "Number of GC content in percent - %0.2f%\n",
                text_struct->gc_content_percent
            ),
        -1);
        fclose(text_struct->file);
        init_struct(text_struct);
    }
    else if (text_struct->filename == NULL) {
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

void gc_percent(TObject *text_struct)
{   // Search GC percent

    text_struct->gc_content =(
        ((float)text_struct->array_number_of_nucleotides[2]
        + (float)text_struct->array_number_of_nucleotides[3])
    );
    text_struct->gc_content_percent = (
        (((float)text_struct->array_number_of_nucleotides[2]
        + (float)text_struct->array_number_of_nucleotides[3])
        / (float)text_struct->length_dna) * 100
    );
}


void percent_nucl(TObject *text_struct)
{   // Search percent of nucleotides

    for (int i = 0; i < NUMBER_OF_NUCLEOTIDES; i++) {
        text_struct->array_percent_of_nucleotides[i] = (
            ((float)text_struct->array_number_of_nucleotides[i]
            / (float)text_struct->length_dna) * 100
        );
    }
}


void count_dna(TObject *text_struct)
{   // Counting dna

    while ((text_struct->bytesRead = fread(
        text_struct->buffer, 1, sizeof(text_struct->buffer),
        text_struct->file)) > 0) {
        for (size_t i = 0; i < text_struct->bytesRead; i++) {
            if (text_struct->buffer[i] > 64 && text_struct->buffer[i] < 91) {
                (text_struct->length_dna)++;
                for (int j = 0; j < NUMBER_OF_NUCLEOTIDES; j++) {
                    if (text_struct->array_of_nucleotides[j] == text_struct->buffer[i]) {
                        (text_struct->length_ATGCU)++;
                        (text_struct->array_number_of_nucleotides[j])++;
                        break;
                    }
            }   }
        }
    }
}






