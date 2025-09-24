#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int range_find(char array[], int digits);

int main(int argc, char *argv[]) {
    int i, file_count, lower_bound, upper_bound, low, up, type = 0;
    char lower_array[5] = {'\0', '\0', '\0', '\0', '\0'};
    char upper_array[5] = {'\0', '\0', '\0', '\0', '\0'};
    char ch, line[100];
    char cut_line[100];
    FILE *file1, *input, *output, *input1, *input2, *out;
    if ((argv[1][0]  < '0') || (argv[1][0]  > '5')) {
        return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt"));
    }
    if ((argv[1][0] == '0') && (argc != 4)) {
        return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt"));
    }
    if (((argv[1][0] == '1') || (argv[1][0] == '2')) && (argc != 5)) {
        return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt"));
    }
    if (((argv[1][0] == '3') || (argv[1][0] == '4') || (argv[1][0] == '5')) && (argc != 3)) {
        return (printf("a.out 0 file1.txt file2.txt\na.out 1 file1.txt file2.txt file3.txt\na.out 2 m-n file1.txt file2.txt\na.out 3 file1.txt\na.out 4 file1.txt\na.out 5 file1.txt"));
    }
    if (argv[1][0] == '2') {       // option 2 is the only one to have a third arguemnt before the files, so the type2 integer indicates that it in option 2 so special precautions can be taken later.
        file_count = 2;
        type = 1;
    } else {
        file_count = argc - 2;      //determines the number of files in argv[]
    }
    if (file_count == 1) {
        file1 = fopen(argv[2], "r");
        if (file1 == NULL) {
            printf("file %s cannot be opened", argv[2]);
            exit(0);
        }
    } else if (file_count == 2) {
        if (type == 1) {  // The read and write files for option 2 are 1 farther to the right than the arguements for option 0 so this if statement takes that into account.
            input = fopen(argv[3], "r"); //option 2
            output = fopen(argv[4], "w");
            if (input == NULL) {
                printf("file %s cannot be opened", argv[3]);
                exit(0);
            }
            if (output == NULL) {
                printf("file %s cannot be opened", argv[4]);
                exit(0);
            }
        } else {   //option 0
            input = fopen(argv[2], "r");
            output = fopen(argv[3], "w");
            if (input == NULL) {
                printf("file %s cannot be opened", argv[2]);
                exit(0);
            }
            if (output == NULL) {
                printf("file %s cannot be opened", argv[3]);
                exit(0);
            }
        }
    } else if (file_count == 3) {
        input1 = fopen(argv[2], "r");
        input2 = fopen(argv[3], "r");
        out = fopen(argv[4], "w");
        if (input1 == NULL) {
            printf("file %s cannot be opened", argv[2]);
            exit(0);
        }
        if (input2 == NULL) {
            printf("file %s cannot be opened", argv[3]);
            exit(0);
        }
        if (out == NULL) {
            printf("file %s cannot be opened", argv[3]);
            exit(0);
        }

    }

    switch (argv[1][0]) {
        case '0':
            while (fscanf(input, "%c", &ch) != EOF){
                fprintf(output, "%c", ch);
            }
            fclose(output);
            fclose(input);
            break;
        case '1':
            while (1==1) {
                if (fgets(line, 100, input1) != NULL) {
                    fprintf(out, "%s", line);
                }
                if (fgets(line, 100, input2) != NULL) {
                    fprintf(out, "%s", line);
                }
                else if ((fgets(line, 100, input1) == NULL) && (fgets(line, 100, input2) == NULL)) {
                    break;
                }
            }
            break;
        case '2':
            i = 0;
            while (((argv[2][i]) <= '9') && ((argv[2][i]) >= '0')) {
                lower_array[i] = argv[2][i];
                i++;
            }
            low = i;
            i++;
            while (((argv[2][i]) <= '9') && ((argv[2][i]) >= '0')) {
                upper_array[i-low-1] = argv[2][i];
                i++;
            }
            up = i-low-1;
            lower_bound = range_find(lower_array, low);
            upper_bound = range_find(upper_array, up);

            while (fgets(line, 100, input) != NULL) {
                for (i = 0; i <= (upper_bound - lower_bound); i++) {
                    cut_line[i] = line[lower_bound-1+i];
                }
                for (i = 0; (i <= (upper_bound - lower_bound)) && (cut_line[i] != '\n'); i++){
                    fprintf(output, "%c", cut_line[i]);
                }
                fprintf(output, "\n");
            }
            break;
        case '3':
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
        case '4':
        case '5':
        default:
    }
    return 0;
}



int range_find(char array[], int digits){
    int k = 0;
    int res = 0;
    digits -= 1;
    for ( ; digits >= 0; digits--){
        res = res + ((array[digits]-48) * (pow(10,k)));
        k++;
    }
    return res;
}