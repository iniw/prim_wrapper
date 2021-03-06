####################
#      Global      #
####################

cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD  20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#####################
#      Project      #
#####################

# Project variables
set(LOCAL_PROJECT_NAME "prim_wrapper")

# Header files
set(HEADERS
    include/arithmetic_traits.hpp
    include/prim_wrapper.hpp
)

# Source files
set(SOURCES
    main.cpp
    tests/benchmark.cpp
    tests/asserts.cpp
)

# Compiler definitions
# make sure to define only one of the tests
set(DEFINES
    #TESTS_BENCHMARK
    TESTS_ASSERTS
)

# Compiler options
set(OPTIONS
    /MP
)

# Project setup
project(${LOCAL_PROJECT_NAME}
        LANGUAGES CXX)

add_executable(${LOCAL_PROJECT_NAME})

target_precompile_headers(${LOCAL_PROJECT_NAME} PRIVATE
<gcem/include/gcem.hpp>
<intrin.h>
<stdlib.h>
<assert.h>
<type_traits>
<concepts>
<cstdint>
<cstddef>
<cmath>
<limits>
<utility>
<string>
<string_view>
<concepts>
<iostream>
<numbers>
<algorithm>
<array>
<sstream>
)

target_include_directories(${LOCAL_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(${LOCAL_PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})
target_compile_definitions(${LOCAL_PROJECT_NAME} PRIVATE ${DEFINES})
target_compile_options(${LOCAL_PROJECT_NAME} PRIVATE ${OPTIONS})

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")

####################
#   Dependencies   #
####################

find_package(benchmark REQUIRED)
target_link_libraries(${LOCAL_PROJECT_NAME} PRIVATE benchmark::benchmark)

find_package(Catch2 REQUIRED)
target_link_libraries(${LOCAL_PROJECT_NAME} PRIVATE Catch2::Catch2)