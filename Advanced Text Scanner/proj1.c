/* Developer: Grady Cronkite
 * This code has 6 options that all do some type of file manipulation and will output an error message if the files or
 * option are inputted in an incorrect way. The first option copies a file into another document.
 * The second option Interleaves the lines from two files into a third.
 * The third option copies one file into another but cuts out all characters that are not within a certain range of line spaces
 * The fourth option mimics the UNIX more command
 * The fifth option mimics the UNIX grep command
 * The sixth option mimics the UNIX wc command
 * This code was written in 3 large chunks: the first three options and the file command checking where written before
 * February 26th, the 4th and 5th options were written before March 4th, and the 6th option remains to be completed on March 11th.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int range_find(char array[], int digits);   //converts a string into an integer
int word_length(char word[]);       //finds the exact length of a word



int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);       // fixes an issue I had where the program would want to read in an input before printing out a printf statement.
    int i, j, k=2, c, file_count, lower_bound, upper_bound, low, up, type = 0;     //Each integer record important values that need to be temporarily held on to
    int line_count = 0;     //used to record the amount of lines in a file
    int word_count = 0;     //used to track the amount of words in a line
    int char_count;         //used to track the amount of chars in a line
    int total_char = 0;     //used to track the total chars in a file
    int total_word = 0;     //used to track the total words in a file
    int longest_word_leg[3] = {0,0,0};      //used tp track the lengths of the three longest words in a file
    int short_line_char_count = 100;        //used to track the length of the shorted line in terms of chars
    int short_line_word_count = 100;        //used to track the length of the shorted line in terms of words
    char short_line_word[100];      //used to record the shortest line in the file based on words
    char short_line_char[100];      //used to record the shortest line the file based on chars
    char lower_array[5] = {'\0', '\0', '\0', '\0', '\0'};      //array that records the lower bound number from option 2
    char upper_array[5] = {'\0', '\0', '\0', '\0', '\0'};      //array that records the upper bound number from option 2
    char ch, line[100];         //line[] records lines taken from one file with the intention of copying it to another file
    char word[30];      //records the word which can be examined by the program
    char cut_line[100];         //used to alter the line stored in line[]
    char search[10] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};      //sets all elements of the char array to null so that '\0' can be used as a marker for the end of a string later
    FILE *file1, *input, *output, *input1, *input2, *out;  //declares each file variable, so they can be opened later on
    if ((argv[1][0]  < '0') || (argv[1][0]  > '5')) {  // checks that they chose an option between 0-5
        return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt\n"));
    }
    if ((argv[1][0] == '0') && (argc != 4)) {  // checks that option 0 has the correct number of arguments
        return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt\n"));
    }
    if (((argv[1][0] == '1') || (argv[1][0] == '2')) && (argc != 5)) {  // checks that options 1 and 2 has the correct number of arguments
        return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt\n"));
    }
    if (((argv[1][0] == '3') || (argv[1][0] == '4') || (argv[1][0] == '5')) && (argc != 3)) {  // checks that options 3 and 4 has the correct number of arguments
        return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt\n"));
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
            i = 0;
            j = 0;
            while (1==1) {      //This loop will alternate printing lines from both input files into the output file until they are both out of lines
                if (fgets(line, 100, input1) != NULL) {     //scans a line from input1 and checks that a line still exists
                    fprintf(out, "%s", line);       //prints the previously scanned line into output
                }
                else {
                    i=1;    //When there are no lines left in the file i is set equal to 1 to indicate that
                }
                if (fgets(line, 100, input2) != NULL) {    //scans a line from input2 and checks that a line still exists
                    fprintf(out, "%s", line);        //prints the previously scanned line into output
                }
                else{
                    j=1;        //When there are no lines left in the file j is set equal to 1 to indicate that
                }
                if (i==1 && j == 1) {  //When both input files run out of lines, the files will be closed and the program will end
                    break;
                }
            }
            fclose(out);  //close all files
            fclose(input1);
            fclose(input2);
            break;
        case '2':       //Option 2
            i = 0;
            if (((argv[2][0]) > '9') || ((argv[2][0]) < '0')) {     //Checks that the m-n condition was correctly inputted and that m and n are numbers rather than words
                return (printf("%s is not in the format of m-n\na.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt\n", argv[2]));
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
                return (printf("%s has m > n\na.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt\n", argv[2]));
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
            while (fgets(line, 100, file1) != NULL){    //runs through each line of the file until it reaches the end
                line_count++;       //increments once for every line in the program, providing an accurate integer value which represents the amount of lines in the file.
            }
            fseek(file1, 0, SEEK_SET);      //sends the code back to the first (or 0th) line of the file
            for (i = 0; i < 10; i++) {      //prints the first 10 lines of the file
                if (fgets(line, 100, file1) != NULL){       //if there is still a line in the file to read, it should be printed out
                    printf("%s", line);
                }
                else {      //if there are no more files in the function, exit the loop
                    break;
                }
                line_count--;       //decreases the amount of lines recorded by the amount that have been printed out
            }
            printf(">>>n for next line, p for next 10 lines, q for quit!<<<\n");
            while (1) {     //this loop will run forever until a break command is presented later
                if (line_count <= 0) {      //if there are no lines left, it should end the program by breaking out of this loop
                    break;
                }
                //else if (line_count < 10) {       //if there are less than 10 lines left, the remaining lines should be printed out
                //    for (i = 0; i < line_count; i++) {      //increments for as many times as there are spaces remaining
                //        fgets(line, 100, file1);
                //        printf("%s", line);
                //    }
                //    break;
                //}

                c = getchar();      //reads an input from the used. It will only respond to an 'n', 'p', or 'q'
                if (c == 'n') {     //if the user inputs an 'n', the program will print the next line in the file
                    fgets(line, 100, file1);    //copies a line from the file into the line string
                    printf("%s", line);     //prints the line string
                    line_count -= 1;        //decreases the line count
                    if (line_count > 0){
                        printf(">>>n for next line, p for next 10 lines, q for quit!<<<\n");
                    }
                }
                if (c == 'p') {     //if the user inputs an 'p', the program will print the next 10 lines in the file
                    for (i = 0; i < 10; i++) {      //increments 10 times
                        fgets(line, 100, file1);        //copies a line from the file into the line string
                        printf("%s", line);         //prints the line string
                        line_count--;       //decreases the line count
                        if (line_count <= 0){
                            break;
                        }
                    }
                    if (line_count > 0){
                        printf(">>>n for next line, p for next 10 lines, q for quit!<<<\n");
                    }
                }
                if (c == 'q') {         //if the user inputs an 'q', the program will break out of the loop and end
                    break;
                }
            }
            fclose (file1);     //closes the file being used
            break;
        case '4':   //Option 4
            printf("Input search string (10 chars max):\n");        //prompts the user for a string to search for
            for (i=0;i<10;i++){       //reads only 10 inputs from the user and adds them to the search string
                ch = getchar();     //reads a character that the user has inputted
                if (ch == '\n'){    //if the character is a '\n' then the for loop should end
                    break;
                }
                search[i] = ch;     //adds the character into the search string
            }
            //scanf("%s", search);        //scans the string that will be searched for
            //search[10] = '\0';      //this will limit the array to 10 elements even if the user inputted more
            j=0;
            while (fgets(line, 100, file1) != NULL){   //loop will repeat as long as there are lines left in the file, it also copies a line of the file into the line string
                for (i=0;i<100;i++){        //increments through all 100 elements of the line string
                    if (line[i] == search[j]){     // if an element of the line string is equal to an element of the search string, j should be incremented by one
                        j++;
                    }
                    else{   //j is reset whenever an element of the line string does not match an element of the search string
                        j = 0;
                    }
                    if (search[j] == '\0'){  //when j has been incremented enough that the end of the string recorded in search is found
                        printf("%s", line);     //print out the line string
                        for (j = 0; j<100; j++){    //sets all elements of the line string to '\0'
                            line[j] = '\0';
                        }
                        j=0;    //reset the value of j
                        break;  //break back into the for loop
                    }
                }
            }
            fclose (file1);     //closes the file being used
            break;
        case '5':   //Option 5
            j=0;
            while (fgets(line, 100, file1) != NULL){        //the loop will end when the file runs our of lines to read
                i=0;
                char_count=0;
                line_count++;       //adds one to the variable for every line the program reads
                char_count++;       //adds one to the variable to account for the first character in every line
                while ((line[i] != '\n') && (line[i] != '\0')){     //the number of chars is counted as i increases, and this ends when the line ends
                    char_count++;
                    i++;
                }
                total_char+=char_count;     //the number of characters in the line is added to the total number of characters in the file
                if (char_count < short_line_char_count){        //if the amount of chars in the line is smaller that the current minimum, it becomes the new minimum value
                    strcpy(short_line_char, line);      //copies the line into the smallest line by chars string
                    short_line_char_count = char_count;     //copies the char count into the smallest line by chars integer
                }
                for ( i = 0; i < 100; i++){     //this loop will increment through every character in the line until it hits a break statement
                    if (isspace(line[i]) || ispunct(line[i])) {         //if the character is white space or punctuation is end the word
                        if (j > 0) {        //if a word is found
                            word_count++;       //increase the amount of words recorded for this line
                            if (word_length(word) >= longest_word_leg[2]) {     //If the length of word is larger or equal to the last element in the longest word array...
                                longest_word_leg[0] = longest_word_leg[1];      //...then the last element is set equal to word and the rest of the elements are sorted
                                longest_word_leg[1] = longest_word_leg[2];
                                longest_word_leg[2] = word_length(word);
                            }
                            else if(word_length(word) >= longest_word_leg[1]) {  //If the length of word is larger or equal to the second element in the longest word array...
                                longest_word_leg[0] = longest_word_leg[1];  //...then the second element is set equal to word and the rest of the elements are sorted
                                longest_word_leg[1] = word_length(word);
                            }
                            else if(word_length(word) > longest_word_leg[0]) {  //If the length of word is larger or equal to the first element in the longest word array...
                                longest_word_leg[0] = word_length(word);     //...then the first element is set equal to word
                            }

                            for (j = 0; j < 30; j++) {    //sets all elements of the word string to '\0' in order to reset it
                                word[j] = '\0';
                            }
                            j = 0;      //resets j
                        }
                    } else {
                        word[j++] = line[i];    //adds a char from line to word and increments j
                    }
                    if(line[i] == '\n'){     //detects the end of the line
                        total_word+=word_count;     //adds the amount of words in the line to the total amount of words in the file
                        if (word_count < short_line_word_count){   //if the amount of words in the line is shorter than the current shortest line...
                            strcpy(short_line_word, line);    //copies the line into the shortest line by word function
                            short_line_word_count = word_count;     //sets the shortest amount of words in a line to the current word count
                        }
                        word_count = 0; //resets word count since it is about to move to the next line
                        break;
                    }
                }
            }
            for (i=0; i < 100; i++){        //this loop exists to go through both strings below and replace the "\n" character at the end of their text to "\0" so it can be formatted easier when printed
                if (short_line_char[i] == '\n'){
                    short_line_char[i] = '\0';
                }
                if (short_line_word[i] == '\n'){
                    short_line_word[i] = '\0';
                }
            }
            printf("The number of characters is: %d\nThe number of words is: %d\nThe number of lines is: %d\nThe shortest line (%d characters): %s\nThe shortest line (%d words): %s\n", total_char, total_word, line_count, short_line_char_count, short_line_char, short_line_word_count, short_line_word);
            printf("The top three longest words are:");
            while (k>=0) {  //Previously, the program found the three largest word lengths. It is now going back through the file to print out three words that match those lengths
                fseek(file1, 0, SEEK_SET);      //resets to the top of the file
                while (fgets(line, 100, file1) != NULL) {    //while there are still lines in the file
                    for (i = 0; i < 100; i++) {
                        if (isspace(line[i]) || ispunct(line[i])) {     //detects the end of a word
                            if (j > 0) {    //detects that the word exists
                                if (word_length(word) == longest_word_leg[k]) {     //The word is printed out if it's length is equal to the integer stored in that element of the array
                                    printf(" %s", word);
                                    k--;    //moves to the next largest word length
                                    if (k>=0){
                                        printf(","); //good formatting
                                    }
                                }
                                for (j = 0; j < 30; j++) {    //sets all elements of the word string to '\0'
                                    word[j] = '\0';     //resets the word string
                                }
                                j=0;        //resets j
                            }
                        } else {
                            word[j++] = line[i];    //adds characters from line into the word string
                        }
                        if (line[i] == '\n') {  //at the end of a line, it should break out of the loop
                            break;
                        }

                    }
                }
            }
            printf("\n");       //ensures this is formatted correctly
            break;
        default:
            return (0);
    }
    return 0;
}



int range_find(char array[], int digits){       //converts a string into an integer
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

int word_length(char word[]){       //finds the exact length of a word
    int i=0;
    int length = 0;     //used to track the length of the word
    while(word[i] != '\0'){ //counts the characters in the word until the end of the word
        length++;
        i++;
    }
    return length;  //returns the length of the word
}


