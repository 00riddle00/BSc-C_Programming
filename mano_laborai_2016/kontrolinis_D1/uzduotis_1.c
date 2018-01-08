/*=============================================================================
 |
 |  Assignment:  Test #1
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 3rd group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  C Programming
 |         Date:  April 28th, 2016
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |   To Compile:  gcc -Wall -xc -g -lm -std=c99 uzduotis_1.c -o uzduotis_1
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  A program which prompts the user to input a positive integer,
 |                and checks whether the number of ones ('1') and ('9') concur.
 |                The output is correspondingly "Yes" or "No".
 |
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <limits.h>

// prompt for entering the number
int get_number();

// get the count of numerals in the number
int get_num_count(int number);

// fill static int array with numerals from the number
void fill_array(int number, int *numberArray);

// check if there are equal size of ones and nines in the number
bool is_valid(int *numberArray, int count);


int main(int argc, char *argv[]) {
    int number = get_number();

    int count = get_num_count(number);

    int *numberArray = malloc(count * sizeof(int));
    if(!numberArray) {
        printf("Memory Error");
        exit(1);
    }

    fill_array(number, numberArray);

    if (is_valid(numberArray, count)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    free(numberArray);
}


int get_number() {
    int number;

    printf("Enter a positive integer\n");
    while (1) {
        printf("> ");
        if ((scanf("%d", &number) == 1) && (number > 0) && (number <= INT_MAX) && (getchar() == '\n')) {
            break;
        } else {
            printf("Please make sure that the number is a positive integer, not exceeding"
                           " MAX_INT value\n");
            while (getchar() != '\n');
        }
    }
    return number;
}


int get_num_count(int number) {

    // current digit position
    int c = 0;
    int n = number;

    while (n != 0) {
        n /= 10;
        c++;
    }
    return c;
}


void fill_array(int number, int *numberArray) {

    int c = 0;
    int n = number;

    // extract each digit
    while (n != 0) {
        numberArray[c] = n % 10;
        n /= 10;
        c++;
    }
}


bool is_valid(int *numberArray, int count) {

    int i;
    int ones = 0;
    int nines = 0;

    for(i = 0; i < count; i++) {
        if (numberArray[i] == 1) {
            ones++;
        }
        if (numberArray[i] == 9) {
            nines++;
        }
    }
    if (ones == nines) {
        return true;
    } else {
        return false;
    }
}
