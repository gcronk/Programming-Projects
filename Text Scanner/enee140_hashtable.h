//
// Created by gjcro on 10/27/2023.
//

#ifndef PROJECT2_ENEE140_HASHTABLE_H
#define PROJECT2_ENEE140_HASHTABLE_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


#define NBUCKETS 50021 //prime number, for better hash uniformity
#define MAX_STRING 80

/*FunctionprototypesforthepublichashtableAPI.*/

void hash_initialize();

float hash_load_factor();

int hash_put(char key[],int value);

int hash_get(char key[]);

int hash_lookup(char key[]);

int index_get(char key[]);

void lowercase_string(char word[]);

int max_collision();

float avg_collision();

#endif //PROJECT2_ENEE140_HASHTABLE_H