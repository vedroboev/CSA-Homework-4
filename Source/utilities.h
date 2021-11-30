#ifndef CSA_HOMEWORK_4_SOURCE_UTILITIES_H_
#define CSA_HOMEWORK_4_SOURCE_UTILITIES_H_

// Error messages.

// Incorrect command format.
int commandFormatError();

// Incorrect size given for random generation.
int wrongSizeError();

// Timed reads and writes.

// Reads container and measures time spent.
void readContainerWithTimer(void* container, int *length, char* filename);

// Generates container and measures time spent.
int generateContainerWithTimer(void* container, int* length, char* size_str);

// Writes container to a file with timer.
void writeContainerWithTimer(void* container, int length, FILE* output, int is_sorted);

#endif //CSA_HOMEWORK_4_SOURCE_UTILITIES_H_
