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

include_directories(
        ${PROJECT_SOURCE_DIR}/include 
)

set(UNIT_TESTS cli_test.cpp)

set(LINK_LIBS cli GTest::GTest GTest::Main)

add_executable(qwik_pirate_unit_test main.cpp ${UNIT_TESTS})

target_link_libraries(qwik_pirate_unit_test ${LINK_LIBS})

gtest_discover_tests(qwik_pirate_unit_test TEST_PREFIX qwikpirate_test:)

install(TARGETS qwik_pirate_unit_test DESTINATION ${CMAKE_INSTALL_DIR}/bin)

