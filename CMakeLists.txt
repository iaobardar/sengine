cmake_minimum_required(VERSION 3.10)

# Project name
project(sengine LANGUAGES C)

# Set the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/glfw-3.4/include) # Add GLFW include directory

# Add GLFW as a subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw-3.4)

# Source files
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.c
)

# Add the executable
add_executable(sengine ${SOURCES})

# Link GLFW to the executable
target_link_libraries(sengine glfw)

# Set build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add debug flags
set(CMAKE_C_FLAGS_DEBUG "-g")

#add_compile_options(-Werror)

#set(CMAKE_VERBOSE_MAKEFILE ON)