#include "structures.h"
#define NUMBER_OF_NUCLEOTIDES 5

void init_struct(TObject *text_struct)
{   // Basic initialization of the structure

    text_struct->length_dna = 0;
    text_struct->length_ATGCU = 0;
    text_struct->gc_content = 0;
    text_struct->gc_content_percent = 0.0;
    int initial_values[NUMBER_OF_NUCLEOTIDES] = {65, 85, 71, 67, 84};
    for (int i = 0; i < NUMBER_OF_NUCLEOTIDES; i++) {
        text_struct->array_of_nucleotides[i] = initial_values[i];
        text_struct->array_number_of_nucleotides[i] = 0;
        text_struct->array_percent_of_nucleotides[i] = 0.0;
    }
}
