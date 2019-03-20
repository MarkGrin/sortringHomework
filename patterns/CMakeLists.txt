cmake_minimum_required (VERSION 2.8)

set (LOGGER_SOURCES logger-src/main.cpp logger-src/logger.cpp)

set (CMAKE_CXX_FLAGS "-std=c++17 -pedantic-errors -g")

add_executable(logger ${LOGGER_SOURCES})
