#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 8192 // Buffer size
#define NUMBER_OF_NUCLEOTIDES 5 // Number of nucleotides


void gc_percent(
    long int *array_number_of_nucleotides,
    float *gc_content_percent, long int *length_dna,
    long int *gc_content
)
{   // Search GC percent
    *gc_content =(
        ((float)array_number_of_nucleotides[2]
        + (float)array_number_of_nucleotides[3])
    );
    *gc_content_percent = (
        (((float)array_number_of_nucleotides[2]
        + (float)array_number_of_nucleotides[3])
        / (float)(*length_dna)) * 100
    );
}


void percent_nucl(
    float *array_percent_of_nucleotides,
    long int *array_number_of_nucleotides,
    long int *length_dna
)
{   // Search percent of nucleotides
    for (int i = 0; i < NUMBER_OF_NUCLEOTIDES; i++) {
        array_percent_of_nucleotides[i] = (
            ((float)array_number_of_nucleotides[i]
            / (float)(*length_dna)) * 100
        );
    }
}


void count_dna(
    char *buffer, size_t *bytesRead, FILE *file,
    int *length_dna, int *length_ATGCU,
    long int *array_number_of_nucleotides,
    int *array_of_nucleotides
)
{   // Counting dna
    while ((*bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        for (size_t i = 0; i < *bytesRead; i++) {
            if (buffer[i] > 64 && buffer[i] < 91) {
                (*length_dna)++;
                for (int j = 0; j < NUMBER_OF_NUCLEOTIDES; j++) {
                    if (array_of_nucleotides[j] == buffer[i]) {
                        (*length_ATGCU)++;
                        array_number_of_nucleotides[j]++;
                        break;
                    }
            }   }
        }
    }
}






