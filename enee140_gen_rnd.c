#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

unsigned m, A, B, X, RND_MAX, M;

int get_user_choice(int lowerBound, int upperBound) {  //Checks to see if an input value is in a certain range 3 times.
    int choice;
    //setbuf(stdout, NULL);
    scanf("%d", &choice);
    if (choice <= upperBound && choice >= lowerBound)  //They got it right the first time
        return choice;
    else {
        printf("\nSorry, that is not a valid option\nEnter your choice (%d-%d):", lowerBound, upperBound);
        scanf("%d", &choice);
        if (choice <= upperBound && choice >= lowerBound)  //They got it right the second time
            return choice;
        else {
            printf("\nSorry, that is not a valid option\nEnter your choice (%d-%d):", lowerBound, upperBound);
            scanf("%d", &choice);
            if (choice <= upperBound && choice >= lowerBound)   //They got it right the Third time
                return choice;
            else {
                printf("You have entered 3 invalid options. Goodbye!");     //They got it wrong three times
                exit(0);        // ends the program
            }
        }
    }
}
void seed_rnd (unsigned seed, int algorithm){
X = seed;
    if (algorithm == 1){  //First Algorithm
        m = 32;
        A = 214013;
        B = 2531011;
    }
    else if (algorithm == 2){ //Second Algorithm
        m = 32;
        A = 1103515245;
        B = 12345;
    }
    else if (algorithm == 3){  //Third Algorithm
        m = 31;
        A = 1103515245;
        B = 12345;
    }
 }

void get_rnd_max(){ // sets RAND_MAX as (2^m)-1
    RND_MAX = (pow(2,m))-1;
}

void gen_rnd() { //step 7 Generate Uniformly-Distributed integers
    M = pow(2,m)-1;
    X = ((A * X) + B) % M;
}
unsigned gen_rnd_limit(unsigned limit){ //Generates a random number which is less than a given limit
    gen_rnd();
    return X % (limit + 1);
}
int gen_rnd_range(int min_gen, int max_gen) {  //Creates a random number within a given range
    if (min_gen > max_gen)
        return 0;
    int range = max_gen - min_gen + 1;  //finds the range of the limits
    gen_rnd();
    return X % range + min_gen;  //returns the value of X modded by the range and increased by the min_gen to bring it back to the original range
}

float gen_rnd_float(float min_gen, float max_gen){  // Generates uniformly distributed floats within a certain range
    float float_x, gen_range;
    if (min_gen > max_gen)
        return 0;

    gen_rnd();
    float_x = X;        //creates a float version of the randomly generated number
    gen_range = max_gen - min_gen; //finds the range of the limits
    float_x /= (float)M;
    float_x = (float_x * gen_range) + min_gen; // the value of X divided by the range and increased by the min_gen to bring it back to the original range
    return float_x;

}

float gen_rnd_exp(float mean){   //generates exponentially distributed floats
    float U, float_x;
    U = gen_rnd_float(0,1);
    if (U == 0)
        U = 0.00001;  // If U = 0, it will be set to an incredibly small value which basically 0 but isn't
    else{
        float_x = (mean*-1)*(log(U));
        return float_x;
    }
}

int main() {
    setbuf(stdout, NULL);
    unsigned rngSeed, minNum, maxNum, x_limit;
    int userChoice, algorithm, x_range, num, i;
    float minFloat, maxFloat, f_range, mean, ex_out;
    printf("Welcome to the ENEE140 pseudo‐random number generator! \n1:Print RND_MAX \n2:Generate uniformly‐distributed positive integers \n3:Generate uniformly‐distributed positive integers, up to a given limit \n4:Generate uniformly‐distributed integers, from a given range \n5:Generate uniformly‐distributed floats, from a given range \n6:Generate exponentially‐distributed floats");
    printf ("\nEnter your choice (1-6):");
    userChoice = get_user_choice(1,6);
    printf ("\nEnter your choice (1-3):");
    algorithm = get_user_choice(1,3);
    printf("\nSelect the seed for the random number generator:");
    scanf("%d", &rngSeed);
    seed_rnd (rngSeed,algorithm);
    if (userChoice == 1){  //Print RND_MAX
        get_rnd_max();
        printf ("%u\n\n", RND_MAX);
        main();
    }
    else if (userChoice == 2) {  // Generate Positive Integers
        printf("\nHow many numbers should I generate:");
        scanf("%d", &num);
        for (i = 1; i <= num; i++) {  //runs the for loop as many times as num equals
            gen_rnd();
            printf("%u ", X);
        }
    }
    else if (userChoice == 3){ //Positive Integers Up To a Given Limit
        printf("How many numbers should I generate:");
        scanf("%d", &num);
        printf("Enter the maximum number to generate:");
        scanf("%u", &maxNum);
        for (i = 1; i <= num; i++) {  //runs the for loop as many times as num equals
            x_limit = gen_rnd_limit(maxNum);
            printf("%u ",x_limit);
        }

    }
    else if (userChoice == 4){ //Integers from a given range
        printf("How many numbers should I generate:");
        scanf("%d", &num);
        printf("Enter the minimum number to generate:");
        scanf("%u", &minNum);
        printf("Enter the maximum number to generate:");
        scanf("%u", &maxNum);

        for (i = 1; i <= num; i++) {  //runs the for loop as many times as num equals
            x_range =  gen_rnd_range(minNum, maxNum);
            printf("%u ",x_range);
        }
    }
    else if (userChoice == 5){ //floats from a given range
        printf("How many numbers should I generate:");
        scanf("%d", &num);
        printf("Enter the minimum number to generate:");
        scanf("%f", &minFloat);
        printf("Enter the maximum number to generate:");
        scanf("%f", &maxFloat);
        for (i = 1; i <= num; i++) {  //runs the for loop as many times as num equals
            f_range =  gen_rnd_float(minFloat, maxFloat);
            printf("%.2f ",f_range);
        }
    }
    else if (userChoice == 6) {     //Exponentially distributed floats
        printf("How many numbers should I generate:");
        scanf("%d", &num);
        printf("Enter the mean of the distribution:");
        scanf("%f", &mean);
        if (mean < 0) {  // if the mean is negative, it will automatically ask for another positive value
            printf("Error: the mean must be a positive number.\nEnter the mean of the distribution:");
            scanf("%f", &mean);
        }
        for (i = 1; i <= num; i++) {  //runs the for loop as many times as num equals
            ex_out = gen_rnd_exp(mean);
            printf("%.2f ", ex_out);
        }
    }
    return 0;
}
