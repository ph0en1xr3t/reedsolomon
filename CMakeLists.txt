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

# Compiler flags - Google C++ Style Guide compliant
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wcast-align -Wformat=2 -Wunused -Wnull-dereference -Wdouble-promotion -Wimplicit-fallthrough")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG -fsanitize=address -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -DGOOGLE_STRIP_LOG=1")

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
    include(FetchContent)
    
    # Fetch Google Test
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0  # Use latest stable version
    )
    
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(googletest)
    
    # Create test executable
    add_executable(tests 
        tests/test_reedsolomon.cpp
        tests/test_galois_field.cpp
        tests/test_encoder.cpp
        tests/test_decoder.cpp
    )
    
    # Link test executable against gtest & gtest_main, gmock & gmock_main
    target_link_libraries(tests 
        ${PROJECT_NAME}
        gtest_main
        gmock_main
    )
    
    # Include test directories
    target_include_directories(tests PRIVATE tests)
    
    # Add tests to CTest
    add_test(NAME reedsolomon_unit_tests COMMAND tests)
    
    # Set test properties
    set_target_properties(tests PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )
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