cmake_minimum_required(VERSION 3.28)
project(ex2_omrishlomy C)

set(CMAKE_C_STANDARD 11)

add_executable(ex2_omrishlomy main.c
        sort_bus_lines.c
        test_bus_lines.c
        test_bus_lines.h
        sort_bus_lines.h)
