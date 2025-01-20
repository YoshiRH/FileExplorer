cmake_minimum_required(VERSION 3.27)

project(fileExplorer VERSION 1.0.0 LANGUAGES C CXX)

set(MAIN_FILE app/main.cpp)

file(GLOB_RECURSE SOURCES src/**/*.cpp)
file(GLOB_RECURSE HEADERS src/**/*.h)

add_executable(fileExplorer ${MAIN_FILE} ${SOURCES} ${HEADERS})