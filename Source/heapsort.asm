; Contains function which perform heapsort on container array.

; I don't show my original swap implementation here, since this one works differently.
; If necessary, the original implementation should still be in the commit history.

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

; Heapifies array at the specified point.
global generateHeapAsm
generateHeapAsm:
section .text
push rbp              ; prologue.
mov rbp, rsp

leave
ret                   ; leaving stack and returning



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