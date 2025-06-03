cmake_minimum_required(VERSION 3.31)
project(shell C)

set(CMAKE_C_STANDARD 23)

add_executable(shell main.c users.c
        commands.c
        commands.h)
