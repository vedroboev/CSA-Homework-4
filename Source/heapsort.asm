; Contains function which perform heapsort on container array.

; I don't show my original swap implementation here, since this one works differently.
; If necessary, the original implementation should still be in the commit history.

extern numberToDouble

; Swaps the two numbers in the container located at specified pointers.
global swapAsm
swapAsm:
section .text
push rbp              ; prologue.
mov rbp, rsp
    mov eax, [rdi]    ; swapping 4-byte number codes of two numbers, using eax as temporary storage
    xchg eax, [rsi]
    mov [rdi], eax

    add rdi, 4        ; moving to next data segment
    add rsi, 4

    mov rax, [rdi]    ; swapping the next 8-byte segments the same way
    xchg rax, [rsi]
    mov [rdi], rax

    add rdi, 8        ; moving to next data segment, swapping again
    add rsi, 8

    mov rax, [rdi]
    xchg rax, [rsi]
    mov [rdi], rax    ; at the end, we will have two 20-byte numbers fully swapped
leave
ret                   ; leaving stack and returning



;void generateHeap(void* container, int index, int length){
;    // Getting largest, left and right as shifts from container beginning.
;    int largest = index;
;    int left = 2 * index + number_size;
;    int right = left + number_size;
;
;    int byte_length = length * number_size;
;
;    // Finding true largest element.
;    if(left < byte_length){
;        if(numberToDouble(container + index) < numberToDouble(container + left)){
;            largest = left;
;        }
;    }
;    if(right < byte_length){
;        if(numberToDouble(container + right) > numberToDouble(container + largest)){
;            largest = right;
;        }
;    }
;
;    // If largest element wasn't truly the largest, we swap it with element at index and try again.
;    if(largest != index){
;        swap(container + largest, container + index);
;        generateHeap(container, largest, length);
;    }
;}

global treeArgs:
treeArgs:
section .text
push rbp
mov rbp, rsp
    mov eax, edx
leave
ret


; Heapifies array at the specified point.
global generateHeapAsm
generateHeapAsm:
section .data
    numsize:    dd 20       ; number size
section .bss
    index:      resd 1      ; various variables, specified in function above
    largest:    resd 1
    left:       resd 1
    right:      resd 1
    length:     resd 1
    container:  resq 1

section .text
push rbp                    ; prologue.
mov rbp, rsp
    mov [container], rdi    ; storing container address from rdi

    mov [index], esi        ; esi contains index, store it
    mov [largest], esi      ; also storing index in largest

    mov eax, esi            ; moving index to eax
    add eax, eax            ; multiplying index by two
    add eax, [numsize]      ; adding one number size
    mov [left], eax         ; writing resulted number to left

    add eax, [numsize]      ; adding another numsize to eax
    mov [right], eax        ; writing to right

    mov [length], edx        ; storing edx (third argument, length) to length


    ; First condition
    cmp [left], eax         ; comparing left with length
    jge .secondCondition    ; if left is bigger than length, skip to next comparison

    mov edx, [index]        ; moving index to edx
    mov rdi, [container]    ; moving container address to rdi
    add rdi, rdx            ; adding index to container to get to the desired element
    call numberToDouble     ; calling number to double, now xmm0 contains the conversion result
    movsd xmm3, xmm0        ; storing result in xmm3 temporarily

    mov edx, [left]         ; doing the same things, but for container + left this time
    mov rdi, [container]
    add rdi, rdx
    call numberToDouble

    comisd xmm3, xmm0       ; comparing two results
    jnb .secondCondition    ; if first is not smaller than second, move to next condition

    mov edx, [left]         ; moving left to largest
    mov [largest], edx


    ; Second condition
    .secondCondition:
    mov eax, [length]       ; moving length to eax
    cmp [right], eax        ; comparing right with length
    jge .swap               ; if right is bigger than length, skip to end

    mov edx, [right]        ; moving right to edx
    mov rdi, [container]    ; moving container address to rdi
    add rdi, rdx            ; adding right to container address
    call numberToDouble     ; converting to double
    movsd xmm3, xmm0        ; storing result in xmm3 temporarily

    mov edx, [largest]      ; doing the same things, but for container + largest this time
    mov rdi, [container]
    add rdi, rdx
    call numberToDouble

    comisd xmm3, xmm0       ; comparing two results
    jna .swap    ; if first is not bigger than second, skip to end

    mov edx, [right]        ; moving right to largest
    mov [largest], edx


    ; Finishing up.
    .swap:
    mov edx, [index]        ; moving index to edx
    mov ecx, [largest]      ; moving largest to ecx
    cmp ecx, edx            ; comparing largest to index
    je .return              ; if equal, we quit the function

    mov rdi, [container]    ; move container address to rdi (that will be argument 1 of swap)
    add rdi, rcx            ; add largest to container
    mov rsi, [container]    ; move container address to rsi (argument 2 of swap)
    add rsi, rdx            ; add index to container
    call swapAsm            ; swap the elements at index and at largest

    mov rdi, [container]    ; move container to rdi (argument 1)
    mov esi, [largest]      ; move largest to esi (argument 2)
    mov edx, [length]       ; moving length to edx (argument 3)
    call generateHeapAsm    ; call the heap generator
.return:
leave
ret                         ; leaving stack and returning



;
;void heapSort(void* container, int length){
;    // Generating a full heap in our container.
;    for (int i = length / 2 - 1; i >= 0; --i) {
;        generateHeap(container, i * number_size, length);
;    }
;
;    // Extracting heap elements in correct order, generating sorted container.
;    for(int i = length - 1; i >= 0; --i){
;        // Moving root to the index.
;        swap(container, container + i * number_size);
;        // Heapifying the partial heap.
;        generateHeap(container, 0, i);
;    }
;}
