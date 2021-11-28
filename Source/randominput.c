// Random input functions for various abstractions.

#include <stdlib.h>
#include <stdio.h>

#include "sharedconstants.h"
#include "container.h"

// Randomly generates an imaginary number.
void generateImaginary(void *pointer) {
    // Generates double im and re in range [-100, 100).
    double im = (double)rand() / RAND_MAX * 200 - 100;
    double re = (double)rand() / RAND_MAX * 200 - 100;
    // Writing data to pointer.
    *(double*)pointer = im;
    *(double*)(pointer + double_size) = re;
}

// Randomly generates a correct fraction.
void generateFraction(void *pointer) {
    // Generates a and b.
    // b is in range [1, 100), a is in range [-100, 100).
    int a = rand() % 200 - 100;
    int b = rand() % 99 + 1;
    // Writing data to pointer,
    *(int*)pointer = a;
    *(int*)(pointer + int_size) = b;
}

// Randomly generates polar coordinates.
void generatePolar(void *pointer) {
    // Generates double angle in range (-pi, pi) and radius in range [0, 100).
    double angle = (double)rand() / RAND_MAX * 2 * PI - PI;
    double radius = (double)rand() / RAND_MAX * 100;
    // Writing data to pointer.
    *(double*)pointer = angle;
    *(double*)(pointer + double_size) = radius;
}

// Randomly generates a generic number.
void generateNumber(void *pointer) {
    // Generating number type.
    int type = rand() % 3 + 1;
    *(int*)pointer = type;
    pointer += int_size;
    // Generating a number of picked type.
    switch (type) {
        case 1 : return generateImaginary(pointer);
        case 2 : return generateFraction(pointer);
        case 3 : return generatePolar(pointer);
        default : return;
    }
}

// Fills a container with the specified amount of randomly generated numbers.
void generateContainer(void *container, int *length, int size) {
    void* pointer = container;
    // Handling incorrect size values.
    if(size <= 0 || size > 10000){
        size = 100;
    }

    for (int i = 0; i < size; ++i) {
        // Writing a generic number and iterating pointer.
        generateNumber(pointer);
        ++(*length);
        pointer += number_size;
    }
}
