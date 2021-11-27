// Input (from file) functions for various abstractions.

#include <stdio.h>

#include "sharedconstants.h"
#include "container.h"

// Reads an imaginary number from string and write it to container.
int readImaginary(char *line, void *pointer) {
    // Checking if all three arguments were read correctly and writing data at the same time.
    if (sscanf(line, "%d%lf%lf", // NOLINT(cert-err34-c)
               (int *) pointer,
               (double *) (pointer + int_size),
               (double *) (pointer + int_size + double_size)) != 3) {
        printf("[Reading Error]: imaginary number could not be read");
        return 0;
    }
    return 1;
}

// Reads a fractional number from string and write it to container.
int readFraction(char *line, void *pointer) {
    // Checking correctness.
    if (sscanf(line, "%d%d%d", // NOLINT(cert-err34-c)
               (int *) pointer,
               (int *) (pointer + int_size),
               (int *) (pointer + 2 * int_size)) != 3) {
        printf("[Reading Error]: fraction could not be read");
        return 0;
    }
    // Checking for zero divisor.
    if (*(int *) (pointer + 2 * int_size) == 0) {
        printf("[Format Error]: fractional divisor given as zero");
        return 0;
    }
    return 1;
}

// Reads polar coordinates from string and writes them to container.
int readPolar(char *line, void *pointer) {
    // Basically the same as reading imaginary.
    if (sscanf(line, "%d%lf%lf", // NOLINT(cert-err34-c)
               (int *) pointer,
               (double *) (pointer + int_size),
               (double *) (pointer + int_size + double_size)) != 3) {
        printf("[Reading Error]: polar coordinates could not be read");
        return 0;
    }
    return 1;
}

// Reads a generalized number from line based on it's code.
int readNumber(char *line, void *pointer) {
    // Reading shape type.
    int type;
    sscanf(line, "%d", &type); // NOLINT(cert-err34-c)

    // Reading the number.
    switch (type) {
        case 1: return readImaginary(line, pointer);
        case 2: return readFraction(line, pointer);
        case 3: return readPolar(line, pointer);
        default:printf("[Reading Error]: incorrect number type found");
            return 0;
    }
}

// Reads and fills up a container from stream.
void readContainer(void *container, int *length, FILE *input) {
    void *pointer = container;
    int line_index = 1;
    // Reading until EOF.
    while (!feof(input)) {
        // Trying to read the current line.
        char line[max_line_length];
        if (!fgets(line, max_line_length, input)) {
            // Handling errors.
            printf("[Reading Error]: line [%d] too long or unreadable.\n", line_index);
        } else {
            // Passing the line to be handled in readNumber.
            if (readNumber(line, pointer)) {
                // Iterating pointer and updating length.
                pointer += number_size;
                ++(*length);
            } else {
                // Handing shape reading errors.
                printf(" at line [%d].\n", line_index);
            }
        }
        line_index++;
    }
}
