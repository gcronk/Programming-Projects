#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int range_find(char array[], int digits);

int main(int argc, char *argv[]) {
    int i, file_count, lower_bound, upper_bound, low, up, type = 0;     //Each integer record important values
    char lower_array[5] = {'\0', '\0', '\0', '\0', '\0'};      //array that records the lower bound number from option 2
    char upper_array[5] = {'\0', '\0', '\0', '\0', '\0'};      //array that records the upper bound number from option 2
    char ch, line[100];         //line[] records lines taken from one file with the intention of copying it to another file
    char cut_line[100];         //used to alter the line stored in line[]
    FILE *file1, *input, *output, *input1, *input2, *out;  //declares each file variable, so they can be opened later on
    if ((argv[1][0]  < '0') || (argv[1][0]  > '5')) {  // checks that they chose an option between 0-5
        return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt"));
    }
    if ((argv[1][0] == '0') && (argc != 4)) {  // checks that option 0 has the correct number of arguments
        return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt"));
    }
    if (((argv[1][0] == '1') || (argv[1][0] == '2')) && (argc != 5)) {  // checks that options 1 and 2 has the correct number of arguments
        return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt"));
    }
    if (((argv[1][0] == '3') || (argv[1][0] == '4') || (argv[1][0] == '5')) && (argc != 3)) {  // checks that options 3 and 4 has the correct number of arguments
        return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt"));
    }
    if (argv[1][0] == '2') {       // option 2 is the only one to have a third argument before the files, so the type2 integer indicates that it in option 2 so special precautions can be taken later.
        file_count = 2;         //determines the number of files in argv[]
        type = 1;       //type indicates that option 2 was recorded
    } else {
        file_count = argc - 2;      //determines the number of files in argv[]
    }
    if (file_count == 1) {
        file1 = fopen(argv[2], "r");        //opens file for reading
        if (file1 == NULL) { //makes sure the file is valid and can be opened
            printf("file %s cannot be opened", argv[2]);
            exit(0);
        }
    } else if (file_count == 2) {
        if (type == 1) {  // The read and write files for option 2 are 1 farther to the right than the arguments for option 0 so this if statement takes that into account.
            input = fopen(argv[3], "r");        //option 2 and opens file for reading
            output = fopen(argv[4], "w");        //opens file for writing
            if (input == NULL) {    //makes sure the file is valid and can be opened
                printf("file %s cannot be opened", argv[3]);
                exit(0);
            }
            if (output == NULL) {   //makes sure the file is valid and can be opened
                printf("file %s cannot be opened", argv[4]);
                exit(0);
            }
        } else {   //option 0
            input = fopen(argv[2], "r");        //opens file for reading
            output = fopen(argv[3], "w");        //opens file for writing
            if (input == NULL) {        //makes sure the file is valid and can be opened
                printf("file %s cannot be opened", argv[2]);
                exit(0);
            }
            if (output == NULL) {       //makes sure the file is valid and can be opened
                printf("file %s cannot be opened", argv[3]);
                exit(0);
            }
        }
    } else if (file_count == 3) {
        input1 = fopen(argv[2], "r");       //opens file for reading
        input2 = fopen(argv[3], "r");       //opens file for reading
        out = fopen(argv[4], "w");      //opens file for writing
        if (input1 == NULL) {       //makes sure the file is valid and can be opened
            printf("file %s cannot be opened", argv[2]);
            exit(0);
        }
        if (input2 == NULL) {       //makes sure the file is valid and can be opened
            printf("file %s cannot be opened", argv[3]);
            exit(0);
        }
        if (out == NULL) {      //makes sure the file is valid and can be opened
            printf("file %s cannot be opened", argv[3]);
            exit(0);
        }

    }

    switch (argv[1][0]) {
        case '0':  //Option 0
            while (fscanf(input, "%c", &ch) != EOF){        //while loop that scans each character from the string and makes sure it is not at the end of the file.
                fprintf(output, "%c", ch);          //prints each scanned character into the output file
            }
            fclose(output);  //close both files
            fclose(input);
            break;
        case '1': //Option 1
            while (1==1) {      //This loop will alternate printing lines from both input files into the output file until they are both out of lines
                if (fgets(line, 100, input1) != NULL) {     //scans a line from input1 and checks that a line still exists
                    fprintf(out, "%s", line);       //prints the previously scanned line into output
                }
                if (fgets(line, 100, input2) != NULL) {    //scans a line from input2 and checks that a line still exists
                    fprintf(out, "%s", line);        //prints the previously scanned line into output
                }
                else if ((fgets(line, 100, input1) == NULL) && (fgets(line, 100, input2) == NULL)) {  //When both input files run out of lines, the files will be closed and the program will end
                    break;
                }
            }
            break;
        case '2':       //Option 2
            i = 0;
            if (((argv[2][0]) > '9') || ((argv[2][0]) < '0')) {     //Checks that the m-n condition was correctly inputted and that m and n are numbers rather than words
                return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt"));
            }
            while (((argv[2][i]) <= '9') && ((argv[2][i]) >= '0')) {      //checks that m and n is given as numbers. This condition also ends when argv[2][i] == '-'
                lower_array[i] = argv[2][i];        //assigns number values to the lower bound character array
                i++;
            }
            low = i;        //low records how many digits have been recorded in the lower_array[]
            i++;
            while (((argv[2][i]) <= '9') && ((argv[2][i]) >= '0')) {    //checks that m and n is given as numbers. This condition also ends when argv[2][i] == '\n'
                upper_array[i-low-1] = argv[2][i];      //assigns number values to the upper bound character array
                i++;
            }
            up = i-low-1;       //up records how many digits have been recorded in the upper_array[]
            lower_bound = range_find(lower_array, low);     // calls function to convert lower_array into an integer
            upper_bound = range_find(upper_array, up);      // calls function to convert upper_array into an integer
            if (upper_bound < lower_bound){     //Checks that the m-n condition was correctly inputted and that m<n. If m>n then there is an error and the main menu is printed and the program will end.
                return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt"));
            }
            while (fgets(line, 100, input) != NULL) {       //checks that the file still has a line to copy from
                for (i = 0; i <= (upper_bound - lower_bound); i++) {
                    cut_line[i] = line[lower_bound-1+i];        //cuts sections of the line into cut_line based on the m-n range
                }
                for (i = 0; (i <= (upper_bound - lower_bound)) && (cut_line[i] != '\n'); i++){      //prints the cut_line array into the output file character by character
                    fprintf(output, "%c", cut_line[i]);     //prints the cut_line array into the output file
                }
                fprintf(output, "\n");      //skips a line in the output file
            }
            fclose(output);  //close all files
            fclose(input1);
            break;
        case '3':       //Option 3: the code for the following case in not yet finished
            for (i = 0; i < 10; i++) {
                fgets(line, 100, file1);
                printf("%s", line);
            }
            if (getchar() == 'n') {
                fgets(line, 100, file1);
                printf("%s", line);
            }
            if (getchar() == 'p') {
                for (i = 0; i < 10; i++) {
                    fgets(line, 100, file1);
                    printf("%s", line);
                }
            }
            if (getchar() == 'q') {
                exit(0);
            }
        case '4':   //Option 4
            break;
        case '5':   //Option 5
            break;
        default:
            return (0);
    }
    return 0;
}



int range_find(char array[], int digits){
    int k = 0;
    int res = 0;        //result that will be printed out later
    int expo = 1;       //represents 10^x
    digits -= 1;
    for ( ; digits >= 0; digits--){     //loop runs a certain number of times depending on the number of digits
        res = res + ((array[digits]-48) * expo);    //calculates the value of the number
        k++;
        expo *= 10;
    }
    return res;         //returns res
}