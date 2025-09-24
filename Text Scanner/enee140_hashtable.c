//
// Created by gjcro on 10/27/2023.
//

#include "enee140_hashtable.h"
#include <string.h>
/* *Define the bucket and hashtable data types. */
typedef struct _bucket{
    char key[MAX_STRING];
    int value;
} Bucket;
typedef Bucket Hashtable[NBUCKETS];
/*
 * *Hashtable main storage */
static Hashtable my_hash_table;
static int used_buckets = 0;
static int max_col=0;
static int sum_col=0;
static int sum_length = 0;


/* *Internal library functions */

void lowercase_string(char word[]){
    int i;
    for(i=0; i < strlen(word); i++) {
        word[i] = tolower(word[i]);  //sets every index in the word array to lowercase
    }
}

unsigned hash_function(char s[])
{
    unsigned hashval, i;

    for(hashval=0, i=0; s[i] != '\0'; i++) {
        hashval += s[i] + 31*hashval;
    }
    return hashval % NBUCKETS;
}

float hash_load_factor() {
    float result;
    if((NBUCKETS - used_buckets) == 0){
        return 1;
    }
    else if ((NBUCKETS - used_buckets) == NBUCKETS){
        return 0;
    }
    else {
        result = (float) used_buckets / (float) NBUCKETS;
        return result;
    }
}

/* *Initialize the hash table by clearing its content. */
void hash_initialize() {
    int i;
    for (i = 0; i < NBUCKETS; i++){
        my_hash_table [i] .key[0]= '\0';
        my_hash_table [i] .value = 0;
    }
    used_buckets = 0;
}

/* *Inserta<key,value>pairinthehashtable. *Return1iftheinsertwassuccessful,and0if *thekeycouldnotbeinsertedbecausethehash *tableiffull. */
int hash_put(char key[],int value) {
    unsigned index, check;
    int collision_counter;
    index = hash_function(key);
    check = index;
    collision_counter = 0;
    do {
        if ((my_hash_table[index].key[0]) == '\0') {
            strcpy(my_hash_table[index].key, key);
            my_hash_table[index].value = value;
            used_buckets++;
            if (max_col < collision_counter){
                max_col = collision_counter;
                //printf("%d", max_col);
            }
            if (collision_counter > 0){
                sum_col += collision_counter;
                sum_length++;
            }
            return 1;
        }
        else if (strncmp(key, my_hash_table[index].key, MAX_STRING) == 0) {
            my_hash_table[index].value = value;
            return 1;
        }
        else {
            index++;
            collision_counter++;
            if (index == NBUCKETS) {
                    index = 0;
            }
        }
    } while (check != index);

    return 0;
}

/* *Ifkeyisstoredinthehashtable,returnthecorresponding *value.Otherwise,return0. */
int hash_get(char key[]) {
    int index;
    if (index_get(key) == -1){
        return 0;
    }
    else {
        index = index_get(key);
        return my_hash_table[index].value;
    }
}
/* *Returns1ifkeyisstoredinthehashtable,and 0 otherwise. */
int hash_lookup(char key[]) {
    int index;
    index = hash_function(key);
    do {
        if ((my_hash_table[index].key[0]) == '\0') {
            return 0;
        }
        else if (strncmp(key, my_hash_table[index].key, MAX_STRING) == 0) {
            return 1;
        }
        else {
            index++;
            if (index == (NBUCKETS)) {
                index = 0;
            }
        }
    } while(1==1);
}

int index_get(char key[]){
    int index;
    index = hash_function(key);
    do {
        if ((my_hash_table[index].key[0]) == '\0') {
            return -1;
        }
        else if (strncmp(key, my_hash_table[index].key, MAX_STRING) == 0) {
            return index;
        }
        else {
            index++;
            if (index == (NBUCKETS)) {
                index = 0;
            }
        }
    } while(1==1);
}

int max_collision(){
    return max_col;
}

float avg_collision(){
    return (float)sum_col/(float)sum_length;
}