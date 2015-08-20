# cmake_minimum_required(VERSION 3.2)
cmake_minimum_required(VERSION 2.8.7)
project(CompGrafica)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    practico_0/pr0_ej1.c
    practico_0/practico_0.h)

add_executable(CompGrafica ${SOURCE_FILES} practico_0/vec3.h practico_0/vec3.c practico_0/Matrix.h practico_0/Matrix.c testSuite/CuTest.h testSuite/CuTest.c testSuite/StrUtil.c testSuite/AllTests.c testSuite/MatrixUtil.c)
