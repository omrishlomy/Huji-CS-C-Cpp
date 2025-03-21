cmake_minimum_required(VERSION 3.28)
project(ex1_omrishlomy C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex1_omrishlomy
        cipher.c
        cipher.h
        main.c
        tests.c
        tests.h)
