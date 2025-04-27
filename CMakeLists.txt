cmake_minimum_required(VERSION 3.10)

# Set the project name
project(sengine C)

# Specify the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the source files
set(SOURCES
    src/main.c
    src/gl.c
)

# Add the executable
add_executable(sengine ${SOURCES})

# Link the libraries
target_link_libraries(sengine
    msvcrt
    ucrt
    msvcprt
    vcruntime
    kernel32
    user32
    gdi32
    shell32
    glfw3
)

# Add the library search path
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Enable warnings as errors
target_compile_options(sengine PRIVATE -Werror)