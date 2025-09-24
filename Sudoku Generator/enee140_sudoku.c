//
// Created by gjcro on 11/15/2023.
//Implementation of the Sudoku library
#include "enee140_sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



int is_valid_board(int board[9][9]) {
    int i, j, count[9];

  //for (i = 0; i < 9; i++) {       //changes lines
  //    for (j = 0; j < 9; j++) {     //rows
  //        if(board[i][j] == '-' )
  //        board[i][j] = 0;
  //    }
  //}

    /*checks that rows are valid*/
    for (i = 0; i < 9; i++) {           //changes lines
        memset(count, 0, sizeof(count));        //sets are places in count to 0
        for (j = 0; j < 9; j++) {     //rows
            if ((board[i][j]) < 0 || (board[i][j]) > 9) {       //if invalid characters are used
                return 0;
            } else if ((board[i][j]) >= 1 && (board[i][j]) <= 9) {      //if the integer is between 1-9, increment the count array in that place
                count[board[i][j] - 1]++;
            }
            if (board[i][j] != 0){
                if(count[board[i][j] - 1] > 1) {           //if any place in the count array is more than one, then the board is not valid
                    return 0;
                }
            }

        }
    }
/* checks that columns are valid*/
    for (i = 0; i < 9; i++) {//changes lines
        memset(count, 0, sizeof(count));        //sets are places in count to 0
        for (j = 0; j < 9; j++) {     //columns
            if ((board[j][i]) < 0 || (board[j][i]) > 9) {       //if invalid characters are used
                return 0;
            } else if ((board[j][i]) >= 1 && (board[j][i]) <= 9) {      //if the integer is between 1-9, increment the count array in that place
                count[board[j][i] - 1]++;
            }
            if (board[i][j] != 0){
                if(count[board[i][j] - 1] > 1) {           //if any place in the count array is more than one, then the board is not valid
                    return 0;
                }
            }
        }
    }

    /*checks that boxes are valid*/
    int c, r, m, n;
    for (c = 0; c < 3; c++) {       //changes between boxes  vertically
        m = 3 * c;
        for (r = 0; r < 3; r++) {       //changes between boxes horizontally
            n = r * 3;
            memset(count, 0, sizeof(count));        //sets are places in count to 0
            for (i = 0 + m; i < 3 + m; i++) {       //changes lines
                for (j = 0 + n; j < 3 + n; j++) {        //rows
                    if ((board[i][j]) < 0 || (board[i][j]) > 9) {       //if a character is not within 1-9 return 0
                        return 0;
                    } else if ((board[i][j]) >= 1 && (board[i][j]) <= 9) {      //if a character is within the 1-9 range, increment count at that place
                        count[board[i][j]]++;
                    }
                    if (board[i][j] != 0){
                        if(count[board[i][j] - 1] > 1) {           //if any place in the count array is more than one, then the board is not valid
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

void generate_permutations(int perms[], int n){
    int i, j, num;
    for (i = 0 ; i<n; i++){         //sets spaces in perms array to 0
        perms[i] = 0;
    }
    for( i = 0 ; i < n ; i++ ) {
        num = rand() % (n+1);       //generates a random number between 0-n
        j = 0;
        do {
            if (perms[j]==num){     //if num is already in perms, don't iterate i
                i--;
                break;
            }
            else if (perms[j] == 0){        //if perms is 0, the space is empty and should have num set in it
                perms[j] = num;
                break;
            }
            else{
                j++;
            }
        } while(j<=n);      //repeat until j = n
    }
}

void transform_permute_rows(int board[9][9]){
    int i,j, band_array[3];
    int perms[9];
    int copy_board[9][9];
    for (i = 0; i < 9; i++) {       //changes lines
        for (j = 0; j < 9; j++) {     //rows
            copy_board[i][j] = board[i][j];     //creates a copy of the board
        }
    }

    for (i = 0; i < 3; i++){  //iterates between rows
        generate_permutations(band_array,3);  //permutes a row
        for (j = 0; j < 3; j++){        //iterates the generated permutations into the perms array
            //printf("%d\n", band_array[j]);
            perms[j+(i*3)]= band_array[j]+3*i-1;        //places 3 permutations into the perms array
        }
    }
    for (i=0; i < 9; i++){
        for (j = 0; j<9;j++){
         board[i][j] = copy_board[perms[i]][j];     //replaces each space in board with permutations using the copy

        }
    }
}

void transform_permute_columns(int board[9][9]){
    int i,j, stack_array[3];
    int perms[9];
    int copy_board[9][9];
    for (i = 0; i < 9; i++) {           //changes columns
        for (j = 0; j < 9; j++) {
            copy_board[i][j] = board[i][j];     //creates a copy of the board
        }
    }

    for (i = 0; i < 3; i++){  //interates between bands
        generate_permutations(stack_array,3);   //permutes a band
        for (j = 0; j < 3; j++){                         //iterates the generated permutations into the perms array
            //printf("%d\n", band_array[j]);
            perms[j+(i*3)]= stack_array[j]+3*i-1;       //places 3 permutations into the perms array
        }
    }
    for (i=0; i < 9; i++){
        for (j = 0; j<9;j++){
            board[i][j] = copy_board[i][perms[j]];  //replaces each space in board with permutations using the copy

        }
    }
}

void transform_permute_bands (int board[9][9]){
    int i,j,k, band_array[3];
    int copy_board[9][9];
    for (i = 0; i < 9; i++) {           //changes lines
        for (j = 0; j < 9; j++) {       //rows
            copy_board[i][j] = board[i][j];     //creates a copy of the board
        }
    }
    generate_permutations(band_array,3);  //permutes a band
    for (k =0; k<3; k++) {              //iterates between bands
        for (i = 0; i < 3; i++) {       //iterates between rows
            for (j = 0; j < 9; j++) {       //iterates between columns
                board[i + (k*3)][j] = copy_board[i + ((band_array[k]-1)*3)][j];     //replaces each space in board with permutations using the copy

            }
        }
    }
}

void transform_permute_stacks (int board[9][9]){
    int i,j,k, stacks_array[3];
    int copy_board[9][9];
    for (i = 0; i < 9; i++) {       //changes lines
        for (j = 0; j < 9; j++) {     //rows
            copy_board[i][j] = board[i][j];         //creates a copy of the board
        }
    }
    generate_permutations(stacks_array,3);  //permutes a band
    for (k =0; k<3; k++) {      //iterates between stacks
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 3; j++) {
                board[i][j+ (k*3)] = copy_board[i][j + ((stacks_array[k]-1)*3)];        //replaces each space in board with permutations using the copy

            }
        }
    }
}

void transform_flip_main_diagonal(int board[9][9]){
    int i,j;
    int copy_board[9][9];
    for (i = 0; i < 9; i++) {       //changes lines
        for (j = 0; j < 9; j++) {     //rows
            copy_board[i][j] = board[i][j];     //creates copy of the board
        }
    }
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            board[i][j] = copy_board[j][i];     //sets board to different parts of the copy
        }
    }
}

void transform_flip_minor_diagonal(int board[9][9]){
    int i,j;
    int copy_board[9][9];
    for (i = 0; i < 9; i++) {       //changes lines
        for (j = 0; j < 9; j++) {     //rows
            copy_board[i][j] = board[i][j];         //creates copy of the board
        }
    }
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            board[i][j] = copy_board[8-j][8-i];     //sets board to different parts of the copy, and starts the copying on the opposite side of the board
        }
    }
}


int print_sudoku_board(int board[9][9]){
    int i,j;
    printf("+-------+-------+-------+\n");      //prints in first line
    for (i = 0; i < 9; i++) {       //changes lines
        printf("| ");       //start every line with |
        for (j = 0; j < 9; j++) {     //rows
            if (board[i][j] == 0) {
                printf("- ");       //if board has a 0 in a space, it should print a 0
            }
            else if ((board [i][j]) >= 1 && (board [i][j]) <= 9){
                printf("%d ",board[i][j]);          //if the integer in board is 1-9 it should be printed
            }
            else{                           //otherwise, return -1 to show that the board is invalid
                return -1;
            }
            if ((j+1)%3 == 0){
                printf("| ");           //every 3 numbers, print a |
            }
        }
        printf("\n");
        if ((i+1)%3 == 0){
            printf("+-------+-------+-------+\n");      //every 3 lines, print this line of + and -
        }
    }
    return 0;
}
void new_sudoku_board(int board[9][9], int blanks){
    srand(time(NULL));
    int i, j, count[] = {1,4,7,2,5,8,3,6,9};        //seed array for the board I will make
    int set[9] ={1,1,1,1,1,1,1,1,1};
    int l=0;

    /* generate a new, solvable, board using count*/
    for (i = 0; i < 9; i++) {//changes lines
        for (j = 0; j < 9; j++) {     //rows
            board[j][i] = count[j]+l;
            if (board[j][i] > 9){       //if the number is larger than 9, it should be set to 1
                board[j][i] = set[j];       //the set array tracks how much a number should be increased by after it was set back to 1 from 9
                set[j]++;
            }
        }
        l++;        //iterates increase in count values
    }
    int x, y;
    for (i = 0; i < blanks; i++){           //runs for as many times as blank equals
        x = rand()%9;       //randomly generates an x value between 1-9
        y = rand()%9;       //randomly generates an y value between 1-9
        if (board[x][y] != 0) {     //if a randomly generated space is not already 0 it should be set to zero
            board[x][y] = 0;
        }
        else{
            i--;        //if a randomly generated space is 0, i-- basically un-increments the for loop and run it again
        }
    }

}



int write_sudoku_board(const char filename[],int board[9][9]){
    int i,j;

    FILE *file;
    file = fopen(filename, "w");        //file is opened to write

    if (file==NULL){            //return -i if the file is empty or can not load
        return -1;      //I/O Error
    }
    for (i = 0; i < 9; i++) {//changes lines
        for (j = 0; j < 9; j++) {     //rows
            if (board[i][j] == 0) {
                fprintf(file,"-");          //if a 0 is in the board, it should be written into the file as a '-'
            }
            else if ((board [i][j]) >= 1 && (board [i][j]) <= 9){           //if the integer in the board is between 1-9, it should be written into the file
                fprintf(file,"%d",board[i][j]);
            }
            else{
                return -2;          //if there is an integer of character that is not between 1-9, return -2
            }
        }
        fprintf(file,"\n");         //move to next line in file
    }
    return 0;
}

int read_sudoku_board(const char filename[],int board[9][9]){
    int i,j;
    char line[12];      //array used to read a whole line of characters from the file

    FILE *file;
    file = fopen(filename, "r");        //file is opened to read

    if (file==NULL){
        return -1;      //file error: file is empty
    }
    for (i = 0; i < 9; i++) {       //changes lines
        if (((fgets(line, 12, file)) == NULL)){     //invalid file format
            return -3;
        }
        for (j = 0; j < 9; j++) {       //rows
            if (line[j] == '\n'){       //invalid file format
                return -3;
            }
            if (line[j] == '-') {       //if a - is found, it should be put into board as a 0
                board[i][j] = 0;
            }
            else if ((line[j]) >= '1' && (line[j]) <= '9'){         //use ascii values of '1'-'9' instead of the actual 1-9 integers
                board[i][j] = line[j] - 48;     //subtract 48 to convert ascii values to decimal values
            }

            else{
                return -2;      //invalid character
            }
        }

    }
    return 0;
}