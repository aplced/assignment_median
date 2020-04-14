cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Median)

include_directories(Median)
set(SOURCE main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})

set(CATCH_INCLUDE_DIR lib/Catch2)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

include_directories(${CATCH_INCLUDE_DIR})
set(TEST_SOURCES test/test_median.cpp)
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES} )
target_link_libraries(${PROJECT_NAME}_tests PUBLIC Catch)