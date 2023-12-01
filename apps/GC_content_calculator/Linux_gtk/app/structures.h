#include <gtk/gtk.h>
#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#define NUMBER_OF_NUCLEOTIDES 5 // Number of nucleotides
#define BUFFER_SIZE 8192 // BufferBuffer size

typedef struct SObject {
    char *filename;
    GtkWidget *text_field;
    FILE *file;
    long int length_dna;
    long int length_ATGCU;
    long int gc_content;
    float gc_content_percent;
    int array_of_nucleotides[NUMBER_OF_NUCLEOTIDES];
    long int array_number_of_nucleotides[NUMBER_OF_NUCLEOTIDES];
    float array_percent_of_nucleotides[NUMBER_OF_NUCLEOTIDES];
    size_t bytesRead;
    char buffer[BUFFER_SIZE];
    char *filename_save_as;
    char *file_write_data;
} TObject;

#endif // STRUCTURES_H_INCLUDED
