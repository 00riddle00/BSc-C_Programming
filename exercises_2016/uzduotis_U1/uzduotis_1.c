/*=============================================================================
 |   Assignment:  Program #1 
 |  Task number:  #19
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 3rd group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  C Programming
 |         Date:  April 7th, 2016
 |
 |     Language:  GNU C (tested using gcc on Lenovo Y50-70, running Arch Linux)
 |     Version:   1.0
 |   To Compile:  gcc -Wall -xc -g uzduotis_1.c -o uzduotis_1
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  When prompted, a user inputs one integer indicating the
 |              size of an array, and then they are prompted to input the 
 |              elements of the integer array in binary notation. The number
 |              of elements should be equal to the defined array size. The
 |              program then prints out all the elements of the array, 
 |              converted to decimal notation.
 |
 |  Constraints:  The program is designed to accept and process only
 |              positive integers.
 |
 |	    Input:    Integer input by user is required by this program.
 |
 |	    Output:   Prompt messages, validation errors and the final results
 |              are displayed one per line to the standard output.
 |
 |
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

// Get the size of the array
int get_array_size();
// Get the elements of the array - binary numbers - to be converted to decimal
// notation
void get_array_elements(int size);
// Check whether the number is binary. If not, print error message and prompt
// for input again
int is_binary(int number);
// Get only unique non-binary numbers in input, used for raising error message
void unique_errors(int array[], int size);
// Convert binary numbers to decimal notation
int binary_to_decimal(int num);


int main(int argc, char *argv[]) {

    printf("Įveskite pasirinktą masyvo dydį (kiek skaičių jis talpins), ne didesnį nei 100:\n");
    int size = get_array_size();
    printf("-----------------------------\n");
    printf("Įveskite dvejetainių skaičių masyvą, kurio dydis yra %d, atskyrę skaičius tarpais. "
                   "Maksimalus skaičius: 1111111111 (10 vienetų):\n", size);
    get_array_elements(size);

    return 0;
}


int get_array_size() {
    int size;

    while (1) {
        printf("> ");
        // checking if input is integer, not greater than MAX_SIZE and greater than zero
        if ((scanf("%d", &size) == 1) && (size <= MAX_SIZE) && (size > 0) && (getchar() == '\n')) {
            break;
        } else {
            printf("Įsitikinkite, kad jūsų įvestas dydis neviršija nustatytos normos, yra sveikas "
                           "skaičius, didesnis už 0\n");
            while (getchar() != '\n');
        }
    }
    return size;
}


void get_array_elements(int size) {
    int array[size];
    int rows;
    bool too_much;
    int i;
    while (1) {
        int str_error_size = 0;
        printf("> ");
        for (i = 0; i < size; i++) {
            if (scanf("%d", &rows) == 1 && (rows >= 0)) {
                array[i] = rows;
            } else {
                array[i] = rows;
                str_error_size += 1;
            }
            if (i == size - 1) {
                too_much = (getchar() == ' ');

            }
        }


        int error_size = 0;

        int error_array[i];
        memset(error_array, 0, sizeof(error_array));

        for (i = 0; i < size; i++) {
            if (!is_binary(array[i])) {
                error_array[i] = array[i];
                error_size += 1;
            }
        }

        char *str_error_msg;

        char *error_head;
        char *error_tail;
        char *try_again = "Bandykite dar kartą.\n";

        if (str_error_size > 0) {
            str_error_msg = "Įveskite tik tinkamus dvejetainius skaičius (maksimalus skaičius: "
                    "1111111111 (10 vienetų).\n";
            printf(str_error_msg);
            printf(try_again);
            while (getchar() != '\n');
        } else if (too_much) {
            printf("Įvėdėte daugiau skaičių, nei nurodyta masyvo dydyje. Įveskite %d "
                           "skaičius.\n", size);
            while (getchar() != '\n');
        } else if (error_size > 0) {
            if (error_size > 1) {
                error_head = "Įvesti skaičiai ";
                error_tail = "nėra dvejetainiai. ";
            } else {
                error_head = "Įvestas skaičius ";
                error_tail = "nėra dvejetainis. ";
            }
            printf(error_head);
            unique_errors(error_array, i);
            printf(error_tail);
            printf(try_again);
        } else {
            break;
        }
    }

    printf("Jūsų skaičiai, konvertuoti į dešimtainę skaičių sistemą:\n");
    for (i = 0; i < size; i++) {
        printf("%d ", binary_to_decimal(array[i]));
    }
    printf("\n");
}


int is_binary(int number) {
    int dv;
    while (number != 0) {
        dv = number % 10;

        if (dv > 1) {
            return 0;
        }
        number /= 10;
    }
    return 1;
}


void unique_errors(int array[], int size) {

    int i;
    int j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < i; j++) {
            if (array[i] == array[j]) {
                break;
            }
        }

        if (i == j && array[i] != 0) {
            // No duplicate element found between index 0 to i
            printf("%d ", array[i]);
        }
    }
}


int binary_to_decimal(int num) {
    int decimal_num = 0, base = 1, rem;
    while (num > 0) {
        rem = num % 10;
        decimal_num = decimal_num + rem * base;
        num = num / 10;
        base = base * 2;
    }
    return decimal_num;
}
