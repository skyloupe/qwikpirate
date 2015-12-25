set(CLI_INC_DIR "${PROJECT_SOURCE_DIR}/include")

include_directories(${CLI_INC_DIR})

set(CLI_SOURCES argv.cpp)

set(CLI_HEADERS ${CLI_INC_DIR}/argv.h)

if(LINUX)
    add_compile_options(-std=c++14 -fPIC)
endif(LINUX)

if(BUILD_SHARED_LIB)
    add_library(cli SHARED ${CLI_HEADERS} ${CLI_SOURCES})
else()
    add_library(cli STATIC ${CLI_HEADERS} ${CLI_SOURCES})
endif()

install(TARGETS cli DESTINATION ${INSTALL_DIR}/lib)

install(FILES ${CLI_HEADERS} DESTINATION ${INSTALL_DIR}/include/cli)


