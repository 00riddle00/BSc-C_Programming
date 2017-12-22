
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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbg.h"
#include "lib_riddle.h"

#define MAX_STRING 50

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
Freq** sort_rlexicographical(Freq** target, int first, int last);

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

    // get number from the user
    int size = get_pos_num("Please enter a number of words > ", 0);

    Histogram* histogram = malloc(sizeof(Histogram));
    if (histogram == NULL) {
        fprintf(stderr, "ERROR: failed to allocate memory\n");
        exit(-1);
    }

    histogram->freqs = malloc(size * sizeof(Freq*));
    if (histogram->freqs == NULL) {
        fprintf(stderr, "ERROR: failed to allocate memory\n");
        exit(-1);
    }

    histogram->size = 0;

    char** words = (char**)malloc(size * sizeof(char*));
    if (words == NULL) {
        fprintf(stderr, "ERROR: failed to allocate memory\n");
        exit(-1);
    }

    for (int i = 0; i < size; i++) {
        words[i] = (char*)malloc(MAX_STRING * sizeof(char));
        if (words[i] == NULL) {
            fprintf(stderr, "ERROR: failed to allocate memory\n");
            exit(-1);
        }
    }

    // get words from the user
    // TODO avoid buffer overflows (string typed is greated than MAX_STRING)
    for (int i = 0; i < size; i++) {
        words[i] = get_word("Enter word > ", words[i]);
    }

    int duplicates;
    int is_duplicate;
    int hist_size = 0;

    // initialize the array of duplicates
    char** duplicated = (char**)malloc(size * sizeof(char*));
    if (duplicated == NULL) {
        fprintf(stderr, "ERROR: failed to allocate memory\n");
        exit(-1);
    }

    for (int i = 0; i < size; i++) {
        duplicated[i] = (char*)calloc(MAX_STRING + 1, sizeof(char));
        if (duplicated[i] == NULL) {
            fprintf(stderr, "ERROR: failed to allocate memory\n");
            exit(-1);
        }
    }

    // count the duplicates of each word and add the word with its duplicate
    // count to the frequency array, and then - to the histogram struct. Each
    // word is writtern once, without duplication.
    for (int i = 0; i < size; i++) {
        is_duplicate = 0;

        // if the word is already added to the duplicate list,
        // it means that its duplicates are already counted,
        // so the loop iteration is skipped
        for (int k = 0; k < size; k++) {
            if (strcmp(duplicated[k], words[i]) == 0) {
                is_duplicate = 1;
            }
        }

        // skipping the loop iteration
        if (is_duplicate) {
            continue;
        }

        // found the word about which we are not yet sure
        // whether it has any duplicates.
        duplicates = 1;
        Freq* freq = malloc(sizeof(Freq));
        if (freq == NULL) {
            fprintf(stderr, "ERROR: failed to allocate memory\n");
            exit(-1);
        }

        freq->word = (char*)malloc(MAX_STRING * sizeof(char));
        if (freq->word == NULL) {
            fprintf(stderr, "ERROR: failed to allocate memory\n");
            exit(-1);
        }
        strcpy(freq->word, words[i]);
        // searching for the duplicates
        for (int j = i + 1; j < size; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                // in case of a duplicate
                // put word in duplicates array
                // and increase its duplicates count
                strcpy(duplicated[i], words[i]);
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
    if (histogram->freqs == NULL) {
        fprintf(stderr, "ERROR: returned NULL pointer\n");
        exit(-1);
    }

    debug("Sorted frequency table:");
    for (int i = hist_size - 1; i >= 0; i--) {
        debug("%s %d", histogram->freqs[i]->word, histogram->freqs[i]->times);
    }
    debug("-----------------------");

    int max_count = histogram->freqs[hist_size - 1]->times;
    int index = hist_size - 1;
    int index_max;

    // partition the frequency array by the same duplicate times, and
    // pass the partitioned array to reverse lexicographical sort
    // on the go.
    for (int i = max_count; i > 0 && index >= 0; i--) {
        index_max = index;
        if (histogram->freqs[index]->times == i) {
            while (index - 1 >= 0 && histogram->freqs[index - 1]->times == i) {
                index--;
            }
            if (index != index_max) {
                histogram->freqs = sort_rlexicographical( histogram->freqs, index, index_max);
                if (histogram->freqs == NULL) {
                    fprintf(stderr, "ERROR: returned NULL pointer\n");
                    exit(-1);
                }
            }
            index--;
        }
    }

    printf("\nLexicographically sorted frequency table:\n");
    print_reverse(histogram->freqs, hist_size);

    // freeing the memory
    for (int i = 0; i < size; i++) {
        free(duplicated[i]);
    }
    free(duplicated);

    for (int i = 0; i < size; i++) {
        free(words[i]);
    }
    free(words);

    for (int i = 0; i < hist_size; i++) {
        free(histogram->freqs[i]->word);
    }

    for (int i = 0; i < hist_size; i++) {
        free(histogram->freqs[i]);
    }
    free(histogram->freqs);
    free(histogram);

    return 0;
}

Freq** quicksort_freqs(Freq** target, int first, int last)
{
    assert(target != NULL && "target cannot be NULL");

    if (first < 0 || last < 0) {
        fprintf(stderr, "ERROR: wrong parameters to '%s'\n", __func__);
        exit(-1);
    }

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

Freq** sort_rlexicographical(Freq** target, int first, int last)
{
    assert(target != NULL && "target cannot be NULL");

    if (first < 0 || last <= 0) {
        fprintf(stderr, "ERROR: wrong parameters to '%s'\n", __func__);
        exit(-1);
    }

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

void print_reverse(Freq** target, int size)
{

    assert(target != NULL && "target cannot be NULL");

    if (size <= 0) {
        fprintf(stderr, "ERROR: wrong size parameters to '%s'\n", __func__);
        exit(-1);
    }

    for (int i = size - 1; i >= 0; i--) {
        printf("%s ", target[i]->word);
        printf("%d \n", target[i]->times);
    }
}
