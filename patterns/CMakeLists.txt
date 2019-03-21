cmake_minimum_required (VERSION 2.8)

set (LOGGER_SOURCES logger-src/main.cpp logger-src/logger.cpp)
set (CHAIN_SOURCES chain-src/main.cpp chain-src/chain.cpp)

set (CMAKE_CXX_FLAGS "-std=c++17 -pedantic-errors -g")

add_executable(logger ${LOGGER_SOURCES})
add_executable(chain ${CHAIN_SOURCES})
