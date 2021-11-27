#ifndef CSA_HOMEWORK_4_SOURCE_CONSTANTS_H_
#define CSA_HOMEWORK_4_SOURCE_CONSTANTS_H_

// Basic constants for type-free solution.

// Integer size on the particular system, also double size to keep things consistent.
int const int_size = sizeof(int);
int const double_size = sizeof(double);

// Constants to store number codes.
int const IMAGINARY = 1;
int const FRACTION = 2;
int const POLAR = 3;

// Constants defining the abstraction sizes.
int const imaginary_size = 2 * sizeof(double);
int const fraction_size = 2 * sizeof(int);
int const polar_size = 2 * sizeof(double);

// Constants for generalized number size + container array size.
int const number_size = sizeof(int) + 2 * sizeof(double);
int const container_size = 10000 * number_size;

int const max_line_length = 100;

double const PI = 3.1415926535;

#endif //CSA_HOMEWORK_4_SOURCE_CONSTANTS_H_