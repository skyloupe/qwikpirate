include_directories(
        ${PROJECT_SOURCE_DIR}/include 
        $ENV{GOOGLE_MOCK_INC_DIR} 
        $ENV{GOOGLE_TEST_INC_DIR}
)

link_directories($ENV{GOOGLE_MOCK_LIB_DIR} $ENV{GOOGLE_TEST_LIB_DIR}) 

set(UNIT_TESTS cli_test.cpp)

add_executable(qwik_pirate_unit_test main.cpp ${UNIT_TESTS})

set(LINK_LIBS cli gmock gtest)
target_link_libraries(qwik_pirate_unit_test ${LINK_LIBS})

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_compile_options(-Wc++11-extensions)
endif()

install(TARGETS qwik_pirate_unit_test DESTINATION ${PROJECT_BINARY_DIR}/bin)

