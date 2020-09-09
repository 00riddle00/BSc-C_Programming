
/*=============================================================================
  |
  |  Assignment:  Test #1
  |
  |       Author:  Tomas Giedraitis
  |  Study group:  VU MIF INFO, 1st group
  |     Contacts:  tomasgiedraitis@gmail.com
  |        Class:  Programming Basics
  |         Date:  December 6th, 2017
  |
  |     Language:  GNU C (using gcc), OS: Arch Linux x86_64)
  |     Version:   0.0
  |
  +-----------------------------------------------------------------------------
  |
  |  Description:  A program which prompts the user to input a n-digit positive
  |                integer, and checks whether the number has duplicates in its
  |                numerals.The output is correspondingly "Yes" (if has no
  |                duplicates) or "No" (if duplicates exist).
  |
  +===========================================================================*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "dbg.h"

#define MAX_STRING 50

// get N-digit number from user
// ::params: message - the prompt message
// ::params: digits - how many digits does the number have
// ::return: collected number
int get_num(char* message, int digits);

// check if number has duplicate numerals
//
// ::params: number - (char array) to be inspected
// ::params: size - size of the char array containing the integer
// ::return: truth value (1 if no duplicates)
int is_distinct(char* number, int size);

int main(int argc, char* argv[])
{
    int digits = 4;
    char message[MAX_STRING];

    sprintf(message, "Enter a %d digit integer:", digits);
    int number = get_num(message, digits);

    char num_to_string[digits + 1];
    sprintf(num_to_string, "%d", number);

    if (is_distinct(num_to_string, digits)) {
        printf("Yes");
    } else {
        printf("No");
    }
    printf("\n");

    return 0;
}

int get_num(char* message, int digits)
{
    int num;
    int min = pow(10, digits - 1);
    int max = pow(10, digits);

    while (1) {
        printf("%s\n> ", message);
        if (scanf("%d", &num) == 1 && getchar() == '\n') {
            if (num >= min && num <= max) {
                break;
            } else {
                printf("Error: input is not a positive %d digit number", digits);
                printf("\n");
            }
        } else {
            while (getchar() != '\n')
                ;
            printf("Error: not a number\n");
        }
    }

    return num;
}

int is_distinct(char* number, int size)
{

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (number[i] == number[j]) {
                //  found a duplicate
                return 0;
            }
        }
    }
    return 1;
}
