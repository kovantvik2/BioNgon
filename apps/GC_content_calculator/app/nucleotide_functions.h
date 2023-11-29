#include <gtk/gtk.h>
#include "structures.h"
#ifndef NUCLEOTIDE_FUNCTIONS_H_INCLUDED
#define NUCLEOTIDE_FUNCTIONS_H_INCLUDED


void gc_percent(
    long int *array_number_of_nucleotides,
    float *gc_content_percent,
    long int *length_dna, long int *gc_content
); // Search GC percent


void percent_nucl(
    float *array_percent_of_nucleotides,
    long int *array_number_of_nucleotides,
    long int *length_dna
); // Search percent of nucleotides


void count_dna(
    char *buffer, size_t *bytesRead, TObject *text_struct,
    int *length_dna, int *length_ATGCU,
    int *array_number_of_nucleotides,
    int *array_of_nucleotides
); // Counting dna

void read_file(GtkWidget *widget, TObject **text_struct); // Read file

#endif // NUCLEOTIDE_FUNCTIONS_H_INCLUDED
