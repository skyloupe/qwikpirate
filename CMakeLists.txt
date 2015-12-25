cmake_minimum_required (VERSION 3.1.0)

project (qwik_pirate)

option(BUILD_UNIT_TESTS "Build Unit Tests" ON)
option(BUILD_SHARED_LIB "Build Unit Tests" ON)

set(INSTALL_DIR ${PROJECT_BINARY_DIR})

add_subdirectory(src)

if(BUILD_UNIT_TESTS)
    add_subdirectory(test)
endif()

