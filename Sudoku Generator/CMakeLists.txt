cmake_minimum_required(VERSION 3.26)
project(Project3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Project3 enee140_gen_sudoku.c
        enee140_sudoku.h
        enee140_sudoku.c)
