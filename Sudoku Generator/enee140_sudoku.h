//
// Created by gjcro on 11/15/2023.
//

#ifndef PROJECT3_ENEE140_SUDOKU_H
#define PROJECT3_ENEE140_SUDOKU_H

int is_valid_board(int board[9][9]);        //checks that board is valid

void generate_permutations(int perms[], int n);     //generates permutations to be used in other functions

void transform_permute_rows(int board[9][9]);       //permutes the rows of the sudoku board

void new_sudoku_board(int board[9][9], int blanks);     //generates a new sudoku board with a certain amount of blank spaces

int print_sudoku_board(int board[9][9]);        //prints the sudoku board in a human-friendly way

void transform_permute_bands (int board[9][9]);     //permutes the bands in the board

void transform_permute_columns(int board[9][9]);        //permutes the columns in the board

void transform_permute_stacks (int board[9][9]);        //permutes the stacks in the board

void transform_flip_main_diagonal(int board[9][9]);     //flips the board along an imaginary axis running through the top left and bottom right corners

void transform_flip_minor_diagonal(int board[9][9]);        //flips the board along an imaginary axis running through the top right and bottom left corners

int read_sudoku_board(const char file_name[],int board[9][9]);      //read a sudoku board from a file

int write_sudoku_board(const char file_name[], int board[9][9]);    //writes a sudoku board into a file

#endif /*PROJECT3_ENEE140_SUDOKU_H*/
