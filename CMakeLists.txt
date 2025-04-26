cmake_minimum_required(VERSION 3.10)

# Project name
project(sengine LANGUAGES C)

# Set the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Link directories
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Source files
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.c
)

# Add the executable
add_executable(sengine ${SOURCES})

# Link libraries
target_link_libraries(sengine
    glfw
    GL
    m
)

# Set build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add debug flags
set(CMAKE_C_FLAGS_DEBUG "-g")