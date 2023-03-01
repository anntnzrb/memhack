cmake_minimum_required(VERSION 3.19)

# project info
set(PROJECT_NAME "memhack")
set(PROJECT_VERSION 1.0)

project(${PROJECT_NAME}
        VERSION ${PROJECT_VERSION}
        DESCRIPTION "A C++ program template for interacting with the memory of Windows processes using the Windows API."
        LANGUAGES CXX)

# language std/flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow")

# dirs
# .cxx files
add_subdirectory(src)

# exe @ bin/
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")