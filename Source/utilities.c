#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "container.h"
#include "utilities.h"

//----------------------------------------------------------------------------------------------------------------------
// ERROR MESSAGES.
//----------------------------------------------------------------------------------------------------------------------

// Incorrect command format.
int commandFormatError(){
    printf("[ERROR] Incorrect command format.\n"
           "Expected one of the following:\n"
           "\tTO READ FROM FILE: command -f <input_file> <output_file> [output_file_sorted]\n"
           "\tTO RANDOMIZE DATA: command -r <container_size> <output_file> [output_file_sorted]\n"
           "View README for more information.\n");
    return 1;
}

// Incorrect size given for random generation.
int wrongSizeError(){
    printf("[ERROR] Incorrect container size.\n"
           "Size should be in range [1, 10000].\n");
    return 2;
}

//----------------------------------------------------------------------------------------------------------------------
// UTILITY FUNCTIONS.
//----------------------------------------------------------------------------------------------------------------------

// Reads container and measures time spent.
void readContainerWithTimer(void* container, int *length, char* filename){
    FILE* input = fopen(filename, "r");

    printf("[START] Reading container from file %s...\n", filename);

    clock_t start = clock();
    readContainer(container, length, input);
    clock_t end = clock();
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[SUCCESS] Read %d/10000 container elements from file %s.\n", *length, filename);
    printf("\tTime spent: %lf seconds.\n", cpu_time);

    fclose(input);
}

// Generates container and measures time spent.
int generateContainerWithTimer(void* container, int* length, char* size_str){
    int size = atoi(size_str); // NOLINT(cert-err34-c)
    if(size <= 0 || size > 10000){
        return wrongSizeError();
    }

    printf("[START] Generating container of size %d randomly...\n", size);

    clock_t start = clock();
    generateContainer(container, length, size);
    clock_t end = clock();
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[SUCCESS] Generated %d/10000 random container elements.\n", *length);
    printf("\tTime spent: %lf seconds.\n", cpu_time);

    return 0;
}

// Writes container to a file with timer.
void writeContainerWithTimer(void* container, int length, FILE* output, int is_sorted){
    printf("[START] Writing %scontainer to file...\n", is_sorted == 0 ? "" : "sorted ");

    fprintf(output,"[%sCONTAINER]\n", is_sorted == 0 ? "" : "SORTED ");

    clock_t start = clock();
    writeContainer(container, length, output);
    clock_t end = clock();
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[SUCCESS] Time spent: %lf seconds.\n", cpu_time);
}