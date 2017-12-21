
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
  |   To Compile:  gcc -Wall -xc -g -lm -std=c99 kontrolinis_1.c -o kontrolinis_1
  |
  +-----------------------------------------------------------------------------
  |
  |  Description:  A program which prompts the user to input a 4-digit positive
  |                integer, and checks whether the number has duplicates in its
  |                numerals.The output is correspondingly "Yes" (if has no
  |                duplicates) or "No" (if duplicates exist).
  |
  |  Errors:       The program starts working incorrectly with sizes bigger than
  |                6 (allows bad inputs).
  |
  +===========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dbg.h"

#define MAX_LINE 256

// get N-digit number from user
// ::params: size - how many digits the number contains
// ::return: collected number (as char array)
char *get_number(int size);

// check if number has duplicate numerals
//
// ::params: number - (char array) to be inspected
// ::params: size - size of the char array containing the integer
// ::return: truth value (1 if no duplicates)
int is_distinct(char *number, int size);


int main(int argc, char *argv[])
{
    int size = 4;

    char *number = get_number(size);
    debug("the number is: %s\n", number);

    if (is_distinct(number, size)) {
        printf("Yes");
    } else {
        printf("No");
    }
    printf("\n");

    return 0;
}



char* get_number(int size) {
    char *num = malloc((size+1)*sizeof(char));
    char err_msg[MAX_LINE];
    sprintf(err_msg, "Please make sure that the input is a number containing %d digits", size);

    printf("Enter a %d digit integer\n", size);
    while (1) {
        printf("> ");

        if (fgets(num, sizeof num, stdin) != NULL) {
            char *p;
            if(p=strchr(num, '\n')){//check exist newline
                *p = 0;
            } else {
                scanf("%*[^\n]");scanf("%*c");//clear upto newline
            }
        } else {
            printf("Read error\n");
            continue;
        }

        if (num[size] != '\0') {
            printf("%s\n", err_msg);
            continue;
        }

        int error = 0;

        for (int i = 0; i < size; i++) {
            if(!isdigit(num[i])) {
                error = 1;
                break;
            }
        }

        if(error) {
            printf("%s\n", err_msg);
            continue;
        }

        break;
    }
    return num;
}


int is_distinct(char *number, int size) {

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


