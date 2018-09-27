cmake_minimum_required (VERSION 2.8)

set (GENERATOR_SOURCES
    src/listNamer.cpp
    src/flat.cpp
    )

set (COMPARATOR_SOURCES
    src/flat.cpp
    )

set (CMAKE_CXX_FLAGS "-std=c++17 -pedantic-errors -g")

add_executable(generator src/generator.cpp ${GENERATOR_SOURCES})
add_executable(comparator src/comparator.cpp ${COMPARATOR_SOURCES})
