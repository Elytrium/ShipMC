cmake_minimum_required(VERSION 3.15)

project(Ship)

file(GLOB_RECURSE SHIP_SOURCES src/*.cpp)

# TODO
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-O2 -fPIC -fomit-frame-pointer -funroll-loops -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fstack-clash-protection -fPIE -Wall -Werror")
set(LDFLAGS "-fuse-ld=lld")

add_executable(Ship ${SHIP_SOURCES})
target_link_libraries(Ship "-Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack -Wl,-z,separate-code -ldeflate")

