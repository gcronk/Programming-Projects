//generate sudoku boards
#include "enee140_sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
unsigned option;        //variable that stores options integer
char difficulty;        //variable that stores difficulty string
int main(int argc, char *argv[]) {
    int i, j, blanks, count[] = {1,4,7,2,5,8,3,6,9};
    int board[9][9];            //the board(duh)
    int set[9] ={1,1,1,1,1,1,1,1,1};
    int l=0;
    char easy[] = "easy", normal[]="normal", hard[]="hard";     //difficulty levels stored as strings

    srand(time(NULL));
    sscanf(argv[3], "%c", &difficulty);     //writes difficulty into string
    sscanf(argv[2], "%u", &option);     //writes options into unsigned integer

/* Generated the fresh sudoku board*/
    for (i = 0; i < 9; i++) {//changes lines
        for (j = 0; j < 9; j++) {     //rows
            board[j][i] = count[j]+l;
            if (board[j][i] > 9){       //if the number is larger than 9, it should be set to 1
                board[j][i] = set[j];       //the set array tracks how much a number should be increased by after it was set back to 1 from 9
                set[j]++;
            }
        }
        l++;   //increments how much count should be increased by
    }

    if ((strcmp(argv[3],easy))== 0){    //easy difficulty generated blanks between 31 and 45
        blanks = (rand()%15)+31;
    }
    if ((strcmp(argv[3],normal)) == 0){    //normal difficulty generated blanks between46 to 51
        blanks = (rand()%6)+46;
    }
    if ((strcmp(argv[3],hard)) == 0){    //hard difficulty generated blanks between 52 to 61
        blanks = (rand()%10)+52;
    }

    /* a piecewise operator is used to evaluate whether each bit is 1 or 0*/
    if (option & 1) {           //if bit 0 is a 1, read in a sudoku board and check its validity
        read_sudoku_board(argv[1],board);
        if (is_valid_board(board) == 0){
            printf("Invalid Board");
            exit(-1);
        }

    }
    else{
        new_sudoku_board(board, blanks);            //if bit 0 is a 0, create a new board
    }
    if ((option >> 1) & 1){     //bit 1
        transform_permute_rows(board);
    }
    if ((option >> 2) & 1){     //bit 2
        transform_permute_bands (board);
    }
    if ((option >> 3) & 1){     //bit 3
        transform_permute_columns(board);
    }
    if ((option >> 4) & 1){         //bit 4
        transform_permute_stacks (board);
    }
    if ((option >> 5) & 1){         //bit 5
        transform_flip_main_diagonal(board);
    }
    if ((option >> 6) & 1){      //bit 6
        transform_flip_minor_diagonal(board);
    }
    if ((option >> 7) & 1){          //bit 7
        print_sudoku_board(board);
    }
    if ((option >> 8) & 1){         //bit 8
        write_sudoku_board(argv[1], board);
    }

    return 0;
}
