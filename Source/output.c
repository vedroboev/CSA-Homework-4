// Output functions for program abstractions.

#include <stdio.h>
#include <math.h>

#include "sharedconstants.h"
#include "container.h"
#include "todouble.h"

// Writes an imaginary number to a file.
void writeImaginary(void *pointer, FILE *output) {
    double re = *((double *) pointer);
    double im = *((double *) (pointer + double_size));
    fprintf(output, "Imaginary number: ");

    // Printing based on re and im equality to 0 and signs.
    if (im == 0) {
        fprintf(output, "%lf.\n", re);
    } else if (re == 0) {
        fprintf(output, "%lfi\n", im);
    } else {
        char sign = im < 0 ? '-' : '+';
        im = im < 0 ? im * -1 : im;
        fprintf(output, "%lf %c %lfi.\n", re, sign, im);
    }

    fprintf(output, "\tConverted to double: %lf.\n", imaginaryToDouble(pointer));

}

// Writes a fractional number to a file.
void writeFraction(void *pointer, FILE *output) {
    int numerator = *((int *) pointer);
    int denominator = *((int *) (pointer + int_size));

    // Converting numbers so that numerator is always positive.
    if (denominator < 0) {
        if (numerator != 0) {
            numerator *= -1;
            denominator *= -1;
        }
    }
    // Printing.
    fprintf(output, "Fraction: %d / %d.\n\tConverted to double: %lf.\n",
            numerator,
            denominator,
            fractionToDouble(pointer));
}

// Writes polar coordinates data to a file.
void writePolar(void *pointer, FILE *output) {
    double angle = *((double *) pointer);
    double radius = *((double *) (pointer + double_size));

    // Getting Cartesian coordinates.
    //double x = radius * cos(angle);
    //double y = radius * sin(angle);

    // Printing.
    fprintf(output, "Polar coordinates: angle = %lf, radius = %lf.\n", angle, radius);
    //fprintf(output, "\tCartesian coordinates: (%lf; %lf).\n", x, y);
    fprintf(output, "\tConverted to double: %lf.\n", polarToDouble(pointer));
}

// Writes a generalized number to a file.
void writeNumber(void *pointer, FILE *output) {
    // Get shape type.
    int type = *((int *) pointer);
    switch (type) {
        case 1: return writeImaginary(pointer + int_size, output);
        case 2: return writeFraction(pointer + int_size, output);
        case 3: return writePolar(pointer + int_size, output);
        default: printf("Writing Error: could not write some part of the container to file.\n");
            fprintf(output, "Incorrect number.\n");
            break;
    }
}

// Writes container and itxs data to an output file.
void writeContainer(void *container, int length, FILE *output) {
    void *pointer = container;
    // Printing container stats.,
    fprintf(output, "CONTAINER CONTENTS:\nContainer has %d/10000 elements.\n", length);
    // Printing all container data.
    for (int i = 0; i < length; ++i) {
        fprintf(output, "%d) ", i + 1);
        writeNumber(pointer, output);
        // Iterating pointer.
        pointer += number_size;
    }
}
