#ifndef CSA_HOMEWORK_4_SOURCE_CONTAINER_H_
#define CSA_HOMEWORK_4_SOURCE_CONTAINER_H_

// Contains some function headers for container.
// This file only exists for the container since only it's functions are used in other files (like main.c).
// There's no need to write separate headers for all number types, since they are isolated.

#include <stdio.h>

// Reads container data from a given stream.
void readContainer(void *container, int* length, FILE *input);
// Prints container data to a given stream.
void writeContainer(void *container, int length, FILE *output);
// Generates a specified number of random numbers and fills container.
void generateContainer(void* container, int* length, int size);
// Main heap sort function.
void heapSort(void *container, int length);

#endif //CSA_HOMEWORK_4_SOURCE_CONTAINER_H_
