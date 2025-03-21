cmake_minimum_required(VERSION 3.22)
project(ex4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex4
        Activation.h
        Activation.cpp
        Dense.h
        main.cpp
        Matrix.h
        MlpNetwork.h
        Matrix.cpp
        Dense.cpp
        MlpNetwork.cpp
)
