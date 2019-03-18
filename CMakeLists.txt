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

set (PRNG_SOURCES
        src/prng.cpp src/xorshift.cpp src/lcm.cpp src/chitest.cpp)

set (HASHER_SOURCES
         src/hash_table.cpp src/flat_h.cpp)

set (CMAKE_CXX_FLAGS "-std=c++17 -pedantic-errors -g")

add_executable(generator src/generator.cpp ${GENERATOR_SOURCES} ${COMMON_SOURCES})
add_executable(comparator src/comparator.cpp ${COMPARATOR_SOURCES} ${COMMON_SOURCES})
add_executable(finder src/finder.cpp ${FINDER_SOURCES} ${COMMON_SOURCES})
add_executable(prng src/prng.cpp ${PRNG_SOURCES})
add_executable(hasher src/hasher.cpp ${HASHER_SOURCES})
