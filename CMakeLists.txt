cmake_minimum_required(VERSION 3.25)
project(WS)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(src)
add_executable(WS ${SOURCES})
