CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(bigint)


add_library(${PROJECT_NAME} "src/main.cpp" "include/bigint.hpp" "include/hexutils.hpp")

target_include_directories(bigint PRIVATE "include")