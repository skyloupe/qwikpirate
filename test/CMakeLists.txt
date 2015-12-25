include_directories(
        ${PROJECT_SOURCE_DIR}/include 
        $ENV{GOOGLE_MOCK_INC_DIR} 
        $ENV{GOOGLE_TEST_INC_DIR}
)

link_directories($ENV{GOOGLE_MOCK_LIB_DIR} $ENV{GOOGLE_TEST_LIB_DIR}) 

set(UNIT_TESTS cli_test.cpp)

add_executable(qwik_pirate_unit_test main.cpp ${UNIT_TESTS})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_compile_options(-std=c++11)
    set(LINK_LIBS cli gmock gtest)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_compile_options(-std=c++11)
    set(LINK_LIBS cli gmock gtest)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_compile_options(-Wc++11-extensions)
    set(LINK_LIBS cli gmock gtest)
endif()

target_link_libraries(qwik_pirate_unit_test ${LINK_LIBS})

install(TARGETS qwik_pirate_unit_test DESTINATION ${PROJECT_BINARY_DIR}/bin)

