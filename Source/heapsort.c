#include "container.h"
#include "sharedconstants.h"

extern void generateHeapAsm(void* container, int index, int length);
extern void swapAsm(void* first, void* second);

// Swaps the two numbers in the container located at specified pointers.
void swap(void* first, void* second){
    // Converting pointers to char.
    unsigned char* first_number = first;
    unsigned char* second_number = second;

    // Swapping two numbers located at these pointers.
    for (int i = 0; i < number_size; ++i) {
        unsigned char temp = *(first_number + i);
        *(first_number + i) = *(second_number + i);
        *(second_number + i) = temp;
    }
}

// Heapifies array at the specified point (element at pointer). Index is passed as a byte shift from array beginning.
void generateHeap(void* container, int index, int length){
    // Getting largest, left and right as shifts from container beginning.
    int largest = index;
    int left = 2 * index + number_size;
    int right = left + number_size;


    // Finding true largest element.
    if(left < length){
        if(numberToDouble(container + index) < numberToDouble(container + left)){
            largest = left;
        }
    }
    if(right < length){
        if(numberToDouble(container + right) > numberToDouble(container + largest)){
            largest = right;
        }
    }

    // If largest element wasn't truly the largest, we swap it with element at index and try again.
    if(largest != index){
        swapAsm(container + largest, container + index);
        generateHeap(container, largest, length);
    }
}

void heapSort(void* container, int length){
    // Generating a full heap in our container.
    for (int i = length / 2 - 1; i >= 0; --i) {
        generateHeap(container, i * number_size, length * number_size);
    }

    // Extracting heap elements in correct order, generating sorted container.
    for(int i = length - 1; i >= 0; --i){
        // Moving root to the index.
        swapAsm(container, container + i * number_size);
        // Heapifying the partial heap.
        generateHeap(container, 0, i * number_size);
    }
}