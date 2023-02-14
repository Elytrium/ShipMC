cmake_minimum_required(VERSION 3.15)

project(Ship)

file(GLOB_RECURSE SHIP_SOURCES src/*.[hc]pp)

# TODO
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-O2 -fPIC -fomit-frame-pointer -funroll-loops -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fstack-clash-protection -fPIE -Wall -Werror")
set(LDFLAGS "-fuse-ld=lld")

set(LIB_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "
        CMake generation is not allowed within the source directory!
        Remove the CMakeCache.txt file and try again from another folder, e.g.:
        mkdir build && cd build
        cmake ..
      ")
endif()

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Build type is not specified, defaulting to Release.")
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(Ship ${SHIP_SOURCES})
target_link_libraries(Ship "-Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack -Wl,-z,separate-code -ldeflate -lpthread")

