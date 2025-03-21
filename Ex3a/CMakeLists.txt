cmake_minimum_required(VERSION 3.28)
project(ex3a_omrishlomy C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex3a_omrishlomy
        markov_chain.c
        markov_chain.h
        tweets_generator.c
        linked_list.c)
