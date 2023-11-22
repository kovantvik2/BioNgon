#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8192 // Buffer size
#define NUMBER_OF_NUCLEOTIDES 5 // Number of nucleotides

void gc_percent(long int *array_number_of_nucleotides, \
                float *gc_content_percent, long int *length_dna, \
                long int *gc_content); // Search GC percent
void percent_nucl(float *array_percent_of_nucleotides, \
                  long int *array_number_of_nucleotides, \
                  long int *length_dna); // Search percent of nucleotides

int main() {
    long int length_dna = 0;
    long int length_ATGCU = 0;
    long int gc_content = 0;
    float gc_content_percent = 0.0;
    int array_of_nucleotides[NUMBER_OF_NUCLEOTIDES] = {65, 85, 71, 67, 84}; // ASCII codes 'A', 'U', 'G', 'C', 'T'
    long int array_number_of_nucleotides[NUMBER_OF_NUCLEOTIDES] = {0, 0, 0, 0, 0};
    float array_percent_of_nucleotides[NUMBER_OF_NUCLEOTIDES] = {0.0, 0.0, 0.0, 0.0, 0.0};
    FILE *f;

    f = fopen("TEST_DNA", "r");
    if (f == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), f)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            if (buffer[i] > 64 && buffer[i] < 91) {
                length_dna++;
                for (int j = 0; j < NUMBER_OF_NUCLEOTIDES; j++) {
                    if (array_of_nucleotides[j] == buffer[i]) {
                        length_ATGCU++;
                        array_number_of_nucleotides[j]++;
                        break;
                    }
            }   }
        }
    }

    fclose(f);

    percent_nucl(&array_percent_of_nucleotides, \
                 &array_number_of_nucleotides, \
                 &length_dna);

    for (int i = 0; i < NUMBER_OF_NUCLEOTIDES; i++) {
        if (array_number_of_nucleotides[i] > 0) {
            printf("%c - %ld - %0.2f%\n", (char) array_of_nucleotides[i], \
                   array_number_of_nucleotides[i], array_percent_of_nucleotides[i]);
        }
    }

    gc_percent(&array_number_of_nucleotides, \
               &gc_content_percent, &length_dna, \
               &gc_content);

    printf("Total number of characters - %ld\n", length_dna);
    printf("Number of ATGCU - %ld\n", length_ATGCU);
    printf("Other characters - %ld\n", length_dna - length_ATGCU);
    printf("Number of GC content in characters - %ld\n", gc_content);
    printf("Number of GC content in percent - %0.2f%\n", gc_content_percent);

    return 0;
}


void gc_percent(long int *array_number_of_nucleotides, \
                float *gc_content_percent, long int *length_dna, \
                long int *gc_content)
{   // Search GC percent
    *gc_content = ((float)array_number_of_nucleotides[2] + (float)array_number_of_nucleotides[3]);
    *gc_content_percent = (((float)array_number_of_nucleotides[2]
                     + (float)array_number_of_nucleotides[3])
                     / (float)(*length_dna)) * 100;
}


void percent_nucl(float *array_percent_of_nucleotides, \
                  long int *array_number_of_nucleotides, \
                  long int *length_dna)
{   // Search percent of nucleotides
    for (int i = 0; i < NUMBER_OF_NUCLEOTIDES; i++) {
        array_percent_of_nucleotides[i] = ((float)array_number_of_nucleotides[i]
                                            / (float)(*length_dna)) * 100;
    }
}
