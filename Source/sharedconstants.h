#ifndef CSA_HOMEWORK_4_SOURCE_SHAREDCONSTANTS_H_
#define CSA_HOMEWORK_4_SOURCE_SHAREDCONSTANTS_H_

// Integer size on the particular system, also double size to keep things consistent.
extern int const int_size;
extern int const double_size;

// Constants to store number codes.
extern int const IMAGINARY;
extern int const FRACTION;
extern int const POLAR;

// Constants defining the abstraction sizes.
extern int const imaginary_size;
extern int const fraction_size;
extern int const polar_size;

// Constants for generalized number size + container array size.
extern int const number_size;
extern int const container_size;

// Maximum number of symbols allowed in one input file line.
extern int const max_line_length;

// Constant for Pi.
extern double const PI;

extern double imaginaryToDouble(void* pointer);
extern double fractionToDouble(void* pointer);
extern double polarToDouble(void* pointer);
extern double numberToDouble(void* pointer);

#endif //CSA_HOMEWORK_4_SOURCE_SHAREDCONSTANTS_H_
