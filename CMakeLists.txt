cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(Median)

# add the executable
add_executable(Median main.cpp)

target_include_directories(Median PUBLIC "${PROJECT_BINARY_DIR}")