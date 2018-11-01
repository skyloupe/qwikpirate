#
#   A silly C++ library to parse command line parameters for your C and C++ programs.
#
#   Copyright (C) 2015  Geoffrey Atkinson
#   
#   Geoffrey Atkinson <gatkinson@skyloupe.com>
#   
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License as published by the Free Software Foundation; either
#   version 3 of the License, or (at your option) any later version.
#   
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#   
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#

cmake_minimum_required(VERSION 3.6.0)

project(qwik_pirate)

option(BUILD_UNIT_TESTS "Build Unit Tests" ON)
option(BUILD_SHARED_LIB "Build Shared Library" OFF)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_compile_options(-fPIC -std=c++11)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_compile_options(-Wc++11-extensions)
endif()

if(MSVC)
# Set compiler options.
set(configs
    CMAKE_C_FLAGS_DEBUG
    CMAKE_C_FLAGS_MINSIZEREL
    CMAKE_C_FLAGS_RELEASEs
    CMAKE_C_FLAGS_RELWITHDEBINFO
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_MINSIZEREL
    CMAKE_CXX_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_RELWITHDEBINFO
)

foreach(config ${configs})
    if(${config} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${config} "${${config}}")
    endif()
endforeach()
endif(MSVC)

add_subdirectory(src)

if(BUILD_UNIT_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    add_subdirectory(test)
endif()

