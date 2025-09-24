#include <stdio.h>

/* *enee140_lookup.c * *Readtheinputline‐by‐line,storethewordsina *hashtable,andallowtheusertolookupseveralwords. */
#include "enee140_hashtable.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_LINE 1000

static int lineIndex;
int next_word(const char line[], char word[], int size);

int prompt_and_check(int max_option);


int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    int choice;
    char word[MAX_STRING],line[MAX_LINE];
    FILE *file;
    //Check command‐line arguments
    if (argc<2){
        fprintf(stderr,"Usage: %s filename\n", argv[0]);
        return -1;
    }
    file = fopen(argv[1],"r");
    if (file == NULL){
        printf("Could not open the %s file.\n",argv[1]);
        exit(-1);
    }
    //Initialize the hash table
    hash_initialize();

    //Read file line‐by‐line
    while (fgets(line, MAX_LINE, file) != NULL){
        //Extracteachwordfromlineandaddittothehashtable
        lineIndex = 0;
        while(next_word(line,word,MAX_STRING)){
           lowercase_string(word);
           //printf("%s\n", word);
          if (hash_lookup(word)) {
              int value = hash_get(word);
              hash_put(word, value + 1);
          }
          else{
              hash_put(word, 1);
          }
        }
    }
    //Print menu and implement project functionality
    printf("Welcome to the ENEE140 word lookup program!\n1. Print hash table statistics\n2. Lookup a word\n3. Exit\n");
    printf("Enter your choice (1-3):");
    scanf("%d",&choice);
    if (choice < 1 || choice > 3){
        do{
        printf("Sorry, that is not a valid option\nEnter your choice (1-3):");
        } while (choice < 1 || choice > 3);
    }
    else if (choice == 1){
        float result = hash_load_factor();
        printf("The load factor is: %f\n", result);
        int max = max_collision();
        printf("The largest length of a collision chain is %d\n", max);
        float avg = avg_collision();
        printf("The average length of a collision chain is %f\n", avg);
    }
    else if (choice == 2){
        char iword[200];
        printf("Enter a word:");
        scanf("%s", word);
        strcpy(iword, word);
        lowercase_string(word);
        if (hash_lookup(word)){
            printf("The word \"%s\" appears %d times. \n", iword, hash_get(word));
        }
        else{
            printf("The word \"%s\" doesn't appear in the input. \n", word);
        }
    }
    else {
        exit(0);
    }
    return 0;
}

int next_word(const char line[], char word[], int size) {
    int wordIndex = 0;
    int i;
    for (i = 0; i < MAX_STRING; i++) {
        word[i] = '\0';
    }

    for ( ; lineIndex < MAX_LINE && line[lineIndex] != '\0'; lineIndex++) {
        if (isspace(line[lineIndex]) || ispunct(line[lineIndex])) {
            if (wordIndex > 0) {
                word[wordIndex] = '\0';
                return 1;
            }
        } else {
            word[wordIndex++] = line[lineIndex];
        }
    }
    if (line[lineIndex] == '\0' || line[lineIndex] == '\n') {
        if (wordIndex > 0) {
            word[wordIndex] = '\0';
            lineIndex = 0;
            return 1;
        }

    }
    lineIndex = 0;
    return 0;
}


