cmake_minimum_required (VERSION 2.8)

set (COMMON_SOURCES
    src/flat.cpp
    )

set (GENERATOR_SOURCES
    src/listNamer.cpp
    )

set (COMPARATOR_SOURCES
    )
set (FINDER_SOURCES
    src/finder.cpp)

set (CMAKE_CXX_FLAGS "-std=c++17 -pedantic-errors -g")

add_executable(generator src/generator.cpp ${GENERATOR_SOURCES} ${COMMON_SOURCES})
add_executable(comparator src/comparator.cpp ${COMPARATOR_SOURCES} ${COMMON_SOURCES})
add_executable(finder src/finder.cpp ${FINDER_SOURCES} ${COMMON_SOURCES})
