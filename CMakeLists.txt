cmake_minimum_required(VERSION 3.0.0)

project(qwik_pirate)

option(BUILD_UNIT_TESTS "Build Unit Tests" ON)
option(BUILD_SHARED_LIB "Build Unit Tests" OFF)

set(INSTALL_DIR ${PROJECT_BINARY_DIR})

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_compile_options(-std=c++11)
endif()

add_subdirectory(src)

if(BUILD_UNIT_TESTS)
    add_subdirectory(test)
endif()

