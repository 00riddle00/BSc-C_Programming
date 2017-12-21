
/*=============================================================================
  |
  |  Assignment:  Test #2
  |
  |       Author:  Tomas Giedraitis
  |  Study group:  VU MIF INFO, 1st group
  |     Contacts:  tomasgiedraitis@gmail.com
  |        Class:  Programming Basics
  |         Date:  December 20th, 2017
  |
  |     Language:  GNU C (using gcc), OS: Arch Linux x86_64)
  |     Version:   0.0
  |   To Compile:  gcc -Wall -xc -g -std=c99 kontrolinis2.c -o kontrolinis_2
  |
  +-----------------------------------------------------------------------------
  |
  |  Description:  (To be added)
  |
  |
  |
  |
  +===========================================================================*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbg.h"
#include "lib_riddle.h"

#define MAX_LINE 256

// get N-digit number from user
// ::params: size - how many digits the number contains
// ::return: collected number (as char array)
char* get_number(int size);

// check if number has duplicate numerals
//
// ::params: number - (char array) to be inspected
// ::params: size - size of the char array containing the integer
// ::return: truth value (1 if no duplicates)
int is_distinct(char* number, int size);

typedef struct Freq {
    char* word;
    int times;
} Freq;

typedef struct Histogram {
    Freq** freqs;
    int size;
} Histogram;

/*        for (i = 0; target[i]->times == z < size - 1; ++i)*/
/*for (j = i + 1; target[i]->times == z; ++j) {*/

/*Freq** sort_lexicographical(Freq** target, int size, int max_count)*/
/*{*/
/*int i, j, z;*/
/*Freq* temp;*/

/*for (z = 1; z <= max_count; ++z) {*/

/*for (i = 0; i < size - 1; ++i)*/

/*for (j = i + 1; j < size; ++j) {*/

/*if (strcmp(target[i]->word, target[j]->word) > 0) {*/
/*temp = target[i];*/
/*target[i] = target[j];*/
/*target[j] = temp;*/
/*}*/
/*}*/
/*}*/

/*printf("\nIn lexicographical order: \n");*/
/*for (i = 0; i < size; ++i) {*/
/*printf("%s\n", target[i]->word);*/
/*}*/

/*return target;*/
/*}*/

// Sort from z to a 
Freq** sort_lexicographical(Freq** target, int first, int last)
{
    int i, j, z;
    Freq* temp;

    for (i = first; i < last; ++i)

        for (j = i + 1; j < last+1; ++j) {

            if (strcmp(target[i]->word, target[j]->word) < 0) {
                temp = target[i];
                target[i] = target[j];
                target[j] = temp;
            }
        }

    printf("\nIn lexicographical order: \n");
    for (i = 0; i < last+1; ++i) {
        printf("%s\n", target[i]->word);
    }

    return target;
}

Freq** quicksort_freqs(Freq** target, int first, int last)
{
    Freq* temp;
    int pivot, j, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (target[i]->times <= target[pivot]->times && i < last) {
                i++;
            }
            while (target[j]->times > target[pivot]->times) {
                j--;
            }
            if (i < j) {
                temp = target[i];
                target[i] = target[j];
                target[j] = temp;
            }
        }
        temp = target[pivot];
        target[pivot] = target[j];
        target[j] = temp;

        quicksort_freqs(target, first, j - 1);
        quicksort_freqs(target, j + 1, last);
    }
    return target;
}

int main(int argc, char* argv[])
{

    // TODO change that
    int stringsize = 10;

    int size = get_pos_num("Please enter a number of words > ", 0);

    /*Freq** histogram = malloc(size * sizeof(Freq));*/
    Histogram* histogram = malloc(sizeof(Histogram));
    histogram->size = 0;
    histogram->freqs = malloc(size * sizeof(Freq*));

    char** words = malloc(size * sizeof(char*));

    for (int i = 0; i < size; i++) {
        words[i] = (char*)malloc(stringsize + 1);
    }

    for (int i = 0; i < size; i++) {
        words[i] = get_word("enter > ", words[i]);
    }

    int duplicates;

    /*    for (int i = 0; i < size; i++) { // read comment by @nbro*/
    /*duplicates = 1;*/
    /*Freq* freq = malloc(sizeof(Freq));*/
    /*freq->word = words[i];*/
    /*for (int j = i + 1; j < size; j++) {*/
    /*if (words[i] == words[j]) {*/
    /*// do whatever you do in case of a duplicate*/
    /*printf("DUPLICATES\n");*/
    /*duplicates++;*/
    /*}*/
    /*}*/
    /*freq->times = duplicates;*/
    /*histogram[i] = freq;*/
    /*printf("%s ", histogram[i]->word);*/
    /*printf("%d ", histogram[i]->times);*/
    /*printf("\n");*/
    /*}*/

    for (int i = 0; i < size; i++) {
        printf("%s ", words[i]);
    }

    // TODO allocate mem dynamically
    char** duplicated = malloc(sizeof(char*));
    for (int i = 0; i < size; i++) {
        duplicated[i] = (char*)malloc(stringsize + 1);
        duplicated[i] = "000";
    }

    int is_duplicate;
    int hist_size = 0;

    for (int i = 0; i < size; i++) { // read comment by @nbro
        is_duplicate = 0;

        for (int s = 0; s < size; s++) {
            if (strcmp(duplicated[s], words[i]) == 0) {
                printf("YES, is duplicate %s\n", words[i]);
                is_duplicate = 1;
            }
        }

        if (is_duplicate) {
            printf("HERE\n");
            continue;
        }

        duplicates = 1;
        Freq* freq = malloc(sizeof(Freq));
        freq->word = words[i];
        for (int j = i + 1; j < size; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                // do whatever you do in case of a duplicate
                printf("DUPLICATES\n");
                duplicated[i] = words[i];
                duplicates++;
            }
        }
        freq->times = duplicates;
        histogram->freqs[histogram->size++] = freq;
        hist_size++;
    }

    debug("%d", hist_size);

    printf("Frequency table: \n");
    for (int i = 0; i < hist_size; i++) {
        printf("%s ", histogram->freqs[i]->word);
        printf("%d \n", histogram->freqs[i]->times);
    }

    histogram->freqs = quicksort_freqs(histogram->freqs, 0, hist_size - 1);

    printf("Sorted frequency table: \n");
    for (int i = hist_size - 1; i >= 0; i--) {
        printf("%s ", histogram->freqs[i]->word);
        printf("%d \n", histogram->freqs[i]->times);
    }

    int max_count = histogram->freqs[hist_size - 1]->times;
    histogram->freqs = sort_lexicographical(histogram->freqs, 0, 2);

    printf("Lexicographically sorted frequency table: \n");
    for (int i = hist_size - 1; i >= 0; i--) {
        printf("%s ", histogram->freqs[i]->word);
        printf("%d \n", histogram->freqs[i]->times);
    }

    return 0;
}
