cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)

project(Ship)

file(GLOB_RECURSE SHIP_SOURCES src/*.[hc]pp)
add_executable(Ship ${SHIP_SOURCES})

# TODO
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_FLAGS "-O2 -fPIC -fomit-frame-pointer -funroll-loops -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fstack-clash-protection -fPIE -Wall -Werror")
target_link_libraries(Ship "-Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack -Wl,-z,separate-code -fuse-ld=lld -ldeflate")
