cmake_minimum_required(VERSION 3.16)

project(reedsolomon
    VERSION 1.0.0
    DESCRIPTION "Reed-Solomon Error Correction Code Implementation"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/reedsolomon.cc
)

# Header files
set(HEADERS
    include/reedsolomon.h
)

# Create library
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "include/reedsolomon.h"
)

# Target include directories
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Enable testing
enable_testing()

# Optional: Create an example executable
option(BUILD_EXAMPLES "Build example programs" ON)
if(BUILD_EXAMPLES)
    add_executable(example examples/main.cpp)
    target_link_libraries(example ${PROJECT_NAME})
endif()

# Optional: Create tests
option(BUILD_TESTS "Build test programs" ON)
if(BUILD_TESTS)
    find_package(GTest QUIET)
    if(GTest_FOUND)
        add_executable(tests tests/test_reedsolomon.cpp)
        target_link_libraries(tests ${PROJECT_NAME} GTest::gtest_main)
        add_test(NAME reedsolomon_tests COMMAND tests)
    endif()
endif()

# Installation
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Config.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
)

# Export from build tree
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)