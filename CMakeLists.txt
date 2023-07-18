cmake_minimum_required(VERSION 3.25)
project(luos C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS -m32)

add_executable(luos main.c)
