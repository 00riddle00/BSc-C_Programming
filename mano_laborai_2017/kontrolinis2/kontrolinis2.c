
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
  |  Description:  The program which gets the input number, which indicates how
  |                many words there will be, then prompts the user to enter
  |                those words, and then displays a histogram in descending 
  |                order by times the word is repeated. The words with the 
  |                same duplicate count are sorted in lexicographical order
  |
  +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbg.h"
#include "lib_riddle.h"

// Frequency structure. Contains the word and the times
// it is repeated
typedef struct Freq {
    char* word;
    int times;
} Freq;

// Histogram structure. Contains the list of frequencies (struct)
// and the size of the list.
typedef struct Histogram {
    Freq** freqs;
    int size;
} Histogram;

// sort the portion of the given array of frequency structs
// in lexicographically reverse order (from z to a) by Freq->word attribute.
//
// ::params: target - array continaing frequency structs
// ::params: first - first index of the portion of the array
// ::params: last - last index of the portion of the array
// ::return: Array of frequency structs (portion of which is
// sorted in lexicographically reverse order)
Freq** sort_lexicographical(Freq** target, int first, int last);

// sort the frequency structs array by their Freq->times
// attribute, using quicksort
//
// ::params: target - the frequency array
// ::params: first - first index of the array
// ::params: first - last index of the array
// ::return: Sorted array of frequency structs
Freq** quicksort_freqs(Freq** target, int first, int last);

// print Frequency array in reverse order, which displays
// the data as in historgram (from bigger to smaller)
//
// ::params: target - the frequency array
// ::params: size - size of the array
void print_reverse(Freq** target, int size);

int main(int argc, char* argv[])
{

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
                is_duplicate = 1;
            }
        }

        if (is_duplicate) {
            continue;
        }

        duplicates = 1;
        Freq* freq = malloc(sizeof(Freq));
        freq->word = words[i];
        for (int j = i + 1; j < size; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                // do whatever you do in case of a duplicate
                duplicated[i] = words[i];
                duplicates++;
            }
        }
        freq->times = duplicates;
        histogram->freqs[histogram->size++] = freq;
        hist_size++;
    }

    debug("Frequency table:");
    for (int i = 0; i < hist_size; i++) {
        debug("%s %d", histogram->freqs[i]->word, histogram->freqs[i]->times);
    }
    debug("-----------------------");

    histogram->freqs = quicksort_freqs(histogram->freqs, 0, hist_size - 1);

    debug("Sorted frequency table:");
    for (int i = hist_size - 1; i >= 0; i--) {
        debug("%s %d", histogram->freqs[i]->word, histogram->freqs[i]->times);
    }
    debug("-----------------------");

    int max_count = histogram->freqs[hist_size - 1]->times;
    int index = hist_size - 1;

    int index_max;
    int index_min;

    for (int i = max_count; i > 0; i--) {
        index_max = index;
        index_min = index;
        if (histogram->freqs[index]->times == i) {
            while (index - 1 >= 0 && histogram->freqs[index - 1]->times == i) {
                index--;
                index_min--;
            }
            if (index_min != index_max) {
                histogram->freqs = sort_lexicographical(
                    histogram->freqs, index_min, index_max);
            }
            index = index_min - 1;
        }
    }

    printf("\nLexicographically sorted frequency table:\n");
    print_reverse(histogram->freqs, hist_size);

    return 0;
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

Freq** sort_lexicographical(Freq** target, int first, int last) 
{
    int i, j;
    Freq* temp;

    for (i = first; i < last; ++i)

        for (j = i + 1; j < last + 1; ++j) {

            if (strcmp(target[i]->word, target[j]->word) < 0) {
                temp = target[i];
                target[i] = target[j];
                target[j] = temp;
            }
        }

    debug("In lexicographical reverse order:");
    for (i = 0; i < last + 1; ++i) {
        debug("%s", target[i]->word);
    }
    debug("-----------------------");

    return target;
}

void print_reverse(Freq** target, int size) {
    for (int i = size - 1; i >= 0; i--) {
        printf("%s ", target[i]->word);
        printf("%d \n", target[i]->times);
    }
}


