#include <stdio.h>
#include <stdlib.h>
#include "nucleotide_functions.h"
#include "interface_gtk.h"

#define BUFFER_SIZE 8192 // Buffer size
#define NUMBER_OF_NUCLEOTIDES 5 // Number of nucleotides
#define FILENAME_SIZE 512



int main(int argc, char *argv[])
{
    long int length_dna = 0;
    long int length_ATGCU = 0;
    long int gc_content = 0;
    float gc_content_percent = 0.0;
    int array_of_nucleotides[NUMBER_OF_NUCLEOTIDES] = {65, 85, 71, 67, 84}; // ASCII codes 'A', 'U', 'G', 'C', 'T'
    long int array_number_of_nucleotides[NUMBER_OF_NUCLEOTIDES] = {0, 0, 0, 0, 0};
    float array_percent_of_nucleotides[NUMBER_OF_NUCLEOTIDES] = {0.0, 0.0, 0.0, 0.0, 0.0};
    //char filename[FILENAME_SIZE];
    char *filename = NULL;
    FILE *file;

    run_interface_gtk_main(argc, &argv, &filename);
    printf("Selected File: %s\n", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    count_dna(
        &buffer, &bytesRead, file,
        &length_dna, &length_ATGCU,
        &array_number_of_nucleotides,
        &array_of_nucleotides
    );

    fclose(file);

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

    /*for (int i = 0; i < NUMBER_OF_NUCLEOTIDES; i++) {
        if (array_number_of_nucleotides[i] > 0) {
            fprintf(output, "%c %ld %0.2f\n", (char) array_of_nucleotides[i], \
                    array_number_of_nucleotides[i], array_percent_of_nucleotides[i]);
        }
    } */


    return 0;
}
