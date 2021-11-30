cmake_minimum_required(VERSION 3.15)
project(CSA_Homework_4 C)

set(CMAKE_C_STANDARD 99)

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/../bin")

set(SOURCE_FILES
        constants.h
        utilities.h
        container.h
        todouble.h
        sharedconstants.h

        main.c
        input.c
        output.c
        randominput.c
        todouble.c
        heapsort.c
        utilities.c)

add_executable(CSA_Homework_4 ${SOURCE_FILES})
