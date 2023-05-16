cmake_minimum_required(VERSION 3.21)
project(ex4_omriaviv)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex4_omriaviv
        main.cpp
        Activation.h
        Dense.h
        Matrix.h
        MlpNetwork.h
        Matrix.cpp
        Activation.cpp
        Dense.cpp
        MlpNetwork.cpp
        #test.cpp
        #test.h
        #test_activation.cpp
        #test_activation.h
        #test_dense.cpp
        #test_dense.h
        #test_matrix.cpp
        #test_matrix.h
        )
