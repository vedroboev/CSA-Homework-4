#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "container.h"
#include "utilities.h"

//----------------------------------------------------------------------------------------------------------------------
// MAIN METHOD.
//----------------------------------------------------------------------------------------------------------------------


int main(int argument_count, char *args[]) {
    // Creating an array which will store all read numbers.
    unsigned char container[container_size];
    int length = 0;


    // Handling incorrect argument count.
    if(argument_count != 5 && argument_count != 4){
        return commandFormatError();
    }

    // Filling container.
    if(!strcmp(args[1], "-f")){
        readContainerWithTimer(container, &length, args[2]);
    } else if(!strcmp(args[1], "-r")){
        generateContainerWithTimer(container, &length, args[2]);
    } else{
        return commandFormatError();
    }

    // Printing container to a file.
    FILE* output = fopen(args[3], "w");
    writeContainerWithTimer(container, length, output, 0);

    // Sorting container.
    heapSort(container, length);

    // Writing sorted container in a separate file if necessary.
    if(argument_count == 5){
        FILE* sorted_output = fopen(args[4], "w");
        writeContainerWithTimer(container, length, sorted_output, 1);
        fclose(sorted_output);
    } else{
        writeContainerWithTimer(container, length, output, 1);
    }

    fclose(output);

    return 0;
}
