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

set(CLI_INC_DIR "${PROJECT_SOURCE_DIR}/include")

include_directories(${CLI_INC_DIR})

set(CLI_SOURCES argv.cpp)

set(CLI_HEADERS ${CLI_INC_DIR}/argv.h
                ${CLI_INC_DIR}/opts.h )

if(BUILD_SHARED_LIB)
    add_library(cli SHARED ${CLI_HEADERS} ${CLI_SOURCES})
else()
    add_library(cli STATIC ${CLI_HEADERS} ${CLI_SOURCES})
endif()

install(TARGETS cli DESTINATION ${INSTALL_DIR}/lib)

install(FILES ${CLI_HEADERS} DESTINATION ${INSTALL_DIR}/include/cli)


