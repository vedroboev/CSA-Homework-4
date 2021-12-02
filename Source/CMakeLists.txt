cmake_minimum_required(VERSION 3.15)
project(CSA_Homework_4 C ASM_NASM)

set(CMAKE_C_STANDARD 99)

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/../bin")

set(ASM_SOURCE_FILES todouble.asm)
set_source_files_properties(${ASM_SOURCE_FILES} PROPERTIES LANGUAGE ASM_NASM)

set(SOURCE_FILES
        constants.h
        utilities.h
        container.h
        sharedconstants.h

        main.c
        input.c
        output.c
        randominput.c
        heapsort.c
        utilities.c

        ${ASM_SOURCE_FILES})


add_executable(CSA_Homework_4 ${SOURCE_FILES})
