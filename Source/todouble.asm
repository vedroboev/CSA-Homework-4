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


;double numberToDouble(void *pointer) {
;    int type = *(int *) pointer;
;    pointer = pointer + int_size;
;
;    switch (type) {
;        case 1 : return imaginaryToDouble(pointer);
;        case 2 : return fractionToDouble(pointer);
;        case 3 : return polarToDouble(pointer);
;        default : return 0;
;    }
;}

; Converting a generic number to double.
global numberToDoubleAsm
numberToDoubleAsm:
section .text
push rbp                        ; prologue.
mov rbp, rsp
    mov eax, [rdi]              ; storing number type in eax

    cmp eax, 1                  ; if type is IMAGINARY
    je .imaginary
    cmp eax, 2                  ; if type is FRACTION
    je .fraction
    cmp eax, 3                  ; if type is POLAR
    je .polar

    mov eax, 0                  ; if type didn't match, we reset eax to 0
    cvtsi2sd xmm0, eax          ; and return it converted to double
    jmp .return

.imaginary:                     ; handing imaginary
    add rdi, 4                  ; moving rdi by int size to get to number data
    call imaginaryToDoubleAsm   ; getting double conversion of specified number
    jmp .return                 ; jumping to the end

.fraction:                      ; handling fraction
    add rdi, 4
    call fractionToDoubleAsm
    jmp .return

.polar:                         ; handling polar
    add rdi, 4
    call polarToDoubleAsm

.return:                        ; leaving stack and returning
leave
ret
