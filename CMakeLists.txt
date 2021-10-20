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

# Header files (relative to "include" directory)
set(HEADERS
    prim_wrapper.hpp
)

# Source files (relative to "src" directory)
set(SOURCES
    main.cpp
)

# Compiler definitions
set(DEFINES
    NOMINNOMAX
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
<gcem/gcem.hpp>
<intrin.h>
<stdlib.h>
<assert.h>
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
<fmt/core.h>
<fmt/format.h>
<fmt/ranges.h>
<fmt/chrono.h>)

list(TRANSFORM HEADERS PREPEND "include/")
list(TRANSFORM SOURCES PREPEND "src/")

target_include_directories(${LOCAL_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(${LOCAL_PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})
target_compile_definitions(${LOCAL_PROJECT_NAME} PRIVATE ${DEFINES})
target_compile_options(${LOCAL_PROJECT_NAME} PRIVATE ${OPTIONS})

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${LOCAL_PROJECT_NAME} PRIVATE fmt::fmt)

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")

####################
#   Dependencies   #
####################