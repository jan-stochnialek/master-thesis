cmake_minimum_required(VERSION 3.10)
project(cpp_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set source files recursively
file(GLOB_RECURSE SOURCES src/*.cpp)

# Include directories
include_directories(include)

add_executable(main ${SOURCES})
