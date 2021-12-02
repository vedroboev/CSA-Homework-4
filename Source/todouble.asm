; Constants for number types.
extern IMAGINARY
extern FRACTION
extern POLAR

; In this file, initial code of the function in C is written before its assembly code.

;double imaginaryToDouble(void *pointer) {
;    double re = *(double *) pointer;
;    double im = *(double *) (pointer + double_size);
;    // Returning imaginary number modulus.
;    return sqrt(re * re + im * im);
;}

; Converting imaginary do double (getting number's modulus).
global imaginaryToDoubleAsm
imaginaryToDoubleAsm:
section .text
push rbp                    ; prologue.
mov rbp, rsp
    movsd xmm0, [rdi]       ; moves real part to xmm0
    movsd xmm1, [rdi + 8]   ; moves imaginary part to xmm1

    mulsd xmm0, xmm0        ; squaring real and imaginary parts
    mulsd xmm1, xmm1

    addsd xmm0, xmm1        ; storing square sum in xmm0

    sqrtsd xmm0, xmm0       ; taking the square root and storing it in xmm0
leave
ret                         ; leaving stack and returning


;double fractionToDouble(void *pointer) {
;    int a = *(int *) pointer;
;    int b = *(int *) (pointer + int_size);
;    return (double) a / b;
;}

; Converts fraction to double (gets division result).
global fractionToDoubleAsm
fractionToDoubleAsm:
section .text
push rbp                        ; prologue.
mov rbp, rsp
    cvtsi2sd xmm0, [rdi]        ; converting numerator to double and storing it in xmm0
    cvtsi2sd xmm1, [rdi + 4]    ; converting denominator to double and storing it in xmm1
    divsd xmm0, xmm1            ; dividing two numbers, result stored in xmm0
leave
ret                             ; leaving stack and returning


;double polarToDouble(void *pointer) {
;    return *(double *) (pointer + double_size);
;}

; Converts polar to double (by getting its radius).
global polarToDoubleAsm
polarToDoubleAsm:
section .text
push rbp                    ; prologue.
mov rbp, rsp
    movsd xmm0, [rdi + 8]   ; moving radius (lies after angle) to xmm0
leave
ret                         ; leaving stack and returning


