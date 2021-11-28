#include "todouble.h"
#include "sharedconstants.h"

// Function definitions for converting numbers to double.

// Custom square root implementation based on Newton's method.
double sqrt(double number) {
    double temp = 0;
    double root = number / 2;

    while (root != temp) {
        temp = root;
        root = (number / temp + temp) / 2;
    }
    return root;
}

// Converting imaginary do double (getting number's modulus).
double imaginaryToDouble(void *pointer) {
    double re = *(double *) pointer;
    double im = *(double *) (pointer + double_size);
    // Returning imaginary number modulus.
    return sqrt(re * re + im * im);
}

// Converts fraction to double (division result).
double fractionToDouble(void *pointer) {
    int a = *(int *) pointer;
    int b = *(int *) (pointer + int_size);
    return (double) a / b;
}

// Converting polar to double (radius).
double polarToDouble(void *pointer) {
    return *(double *) (pointer + double_size);
}

// Converting a generic number to double.
double numberToDouble(void *pointer) {
    int type = *(int *) pointer;
    pointer = pointer + int_size;

    switch (type) {
        case 1 : return imaginaryToDouble(pointer);
        case 2 : return fractionToDouble(pointer);
        case 3 : return polarToDouble(pointer);
        default : return 0;
    }
}
