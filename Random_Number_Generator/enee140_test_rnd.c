#include <stdio.h>
#include <math.h>

int main() {
    setbuf(stdout, NULL);
    int length, i, input, o, length_Test = 0;
    char space;
    float e, difference_o_e, D = 0;
    int bin[10] = {0};
    printf("How many numbers were generated:");
    scanf("%d", &length);
    printf("What is the sequence of randomly generated numbers:");
    for (i = 0; i < length; i++) {
        scanf("%d%c", &input, &space);
        length_Test++;
        if (input >= 0 && input <= 99) {
            if (input >= 0 &&
                input <= 9)  //If a value fits into a certain bin, then 1 is added to the value of that bin
                bin[0]++;
            else if (input >= 10 && input <= 19)
                bin[1]++;
            else if (input >= 20 && input <= 29)
                bin[2]++;
            else if (input >= 30 && input <= 39)
                bin[3]++;
            else if (input >= 40 && input <= 49)
                bin[4]++;
            else if (input >= 50 && input <= 59)
                bin[5]++;
            else if (input >= 60 && input <= 69)
                bin[6]++;
            else if (input >= 70 && input <= 79)
                bin[7]++;
            else if (input >= 80 && input <= 89)
                bin[8]++;
            else if (input >= 90 && input <= 99)
                bin[9]++;
        }
        else {
            printf("%d is not in the [0,99] range.", input);
            return 0;
        }
        if (space == '\n' && length_Test < length) {
            printf("%d numbers are required, but only %d were provided.", length, length_Test);
            return 0;
        }
    }
    for (i = 0; i < 10; i++) {
        o = bin[i];
        e = (float) length / 10;
        difference_o_e = (float) o - e;
        D = D + (pow(difference_o_e, 2) / e);


    }
    if (D <= 14.684)
        printf("The sequence is consistent with the uniform distribution (D = %.2f).", D);
    else if (D > 14.684 && D <= 21.666)
        printf("The sequence is suspicious (D = %.2f).", D);
    else if (D > 21.666)
        printf("The sequence is unlikely to come from a uniform distribution (D = %.2f).", D);
    return 0;
}
