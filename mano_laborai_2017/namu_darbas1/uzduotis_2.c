/*=============================================================================
 |
 |  Assignment:  Program #2
 |  Task number:  #19
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 3rd group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  C Programming
 |         Date:  April 20th, 2016
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |   To Compile:  gcc -Wall -xc -g -lm -std=c99 uzduotis_2.c -o uzduotis_2
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  A number conversion program, where one can choose the type
 |                of conversion and input option (normal, random) and save
 |                both original and converted arrays to a database, which is
 |                then saved to a file. Currently it supports converting binary
 |                numbers to decimal notation. After creating database
 |                entries, user can retrieve or list entries, delete or
 |                update them. Database saving to a file is not yet supported.
 |
 |  Constraints:  [1] When a user is prompted for an integer or integer array,
 |                the program is designed to accept and process only  positive
 |                integers.
 |                [2] Maximum binary number accepted is 1111111111.
 |                [3] Maximum size of an array is 100.
 |
 |	    Input:    Command line input by user
 |
 |	    Output:   Prompt messages, validation errors and final results
 |                are displayed one per line to the standard output.
 |
 |  Known bugs:   [1] After prompting user to update an entry, a second
 |                prompt to delete the entry appears, which is not needed and
 |                should be implied.
 |                [2] Segmentation fault on integer array input (have not yet
 |                been reproduced, happened with 50 integers on input.
 |                [3] Segmentation fault on input integers whose numeral count
 |                is 7, 8, 9
 |                [4] If user input exceeds the line buffer, the buffer is not
 |                cleared after
 |                that and next input scan takes old values.
 |
 |      TODOS:    [1] Supplement code with coherent comments (there are too
 |                few comments yet).
 |                [2] Change multiple variable names to be more coherent
 |                [3] Implement 'back' action to drop current changes and get
 |                back to the main shell.
 |                [4] String input validation fix - ex. 's' and 'set' works,
 |                but also does 'se', which should not.
 |                [5] Make line buffers into dynamic arrays
 |                [6] Implement saving to a file.
 |                [7] Implement getting input from argv[] on program start.
 |                [8] Remove goto statements
 |
 | Version
 | updates:     Currently this is the intial version
 |
 +===========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <time.h>


#define MAX_SIZE 100
#define MAX_DATA 1536
#define MAX_NUMBER_SIZE 10
#define MAX_ROWS 100


// struct to always track int array's size
typedef struct {
    int size;
    int *elements;
} Array;

// database address ('set' - whether is set (exists) or not)
// contain both decimal and binary arrays
typedef struct {
    int id;
    int set;
    Array *decimal_array;
    Array *binary_array;
} Address;

// database
typedef struct {
    Address rows[MAX_ROWS];
} Database;


// print out the error message and exits.
// use only in case of memory errors.
void die();

// prompt for user input ([Y/n])
//
// ::params: message - prompt message
// ::return: (decision (yes or no))
bool choice(const char *message);

// check if the parameter (argv[1])
// is valid (as the size of an array)
//
// ::params: size - size of an array (raw input)
bool parameter_valid(int size);

// prompt user for input (the main shell)
// validate input
//
// ::return: params (array of input parameters (max = 3))
char **get_input();

// free duplicated strings in scanning
// user input (fuction: get_input())
//
// ::params: params - (array of input parameters (max = 3))
void free_dup(char ***params);

// prompt for entering array size
//
// ::return: size
int get_array_size();

// prompt for entering numbers of the array
// modify passed pointer
//
// ::params: binary_array
void get_array_elements(Array *binary_array);

// generate random binary numbers (extract
// size of array from struct passed to function
//
// params: binary_array
void random_binary(Array *binary_array);

// check if number is binary
//
// ::params: each number is passed from the array
// ::return: (bool)
bool is_binary(int number);

// from array of errors, remove duplicates
// and print the error values (non-binary number)
//
// ::params: array - error array
// ::params: size - size of error array
void unique_errors(int *array, int size);

// convert binary to decimal. Initialize new array
// inside the function and return it.
//
// ::params: array - binary array
// ::return: Array - decimal array
Array *binary_to_decimal(Array *array);

// allocate space and create database
// (initialize Address structs)
//
// ::return: Database
Database *database_create();

// set Address struct (containing two dynamic arrays) in database
//
// ::params: db - Database
// ::params: id - entry id (user input)
// ::params: binary array
// ::params: decimal_array
void database_set(Database *db, int id, Array *binary, Array *decimal_array);

// get address from database
//
// ::params: db - Database
// ::params: id - entry id (user input)
void database_get(Database *db, int id);

// get address from database
//
// ::params: db - Database
void database_list(Database *db);

// print address from database
//
// ::params: addr - Address
void address_print(Address *addr);

// delete address from database
//
// ::params: db - Database
// ::params: id - entry id (user input)
void database_delete(Database *db, int id);

// [1] free two Array's (struct) elements in Address (struct)
// [2] free two Array's (struct) in Address (struct)
//
// ::params: cur - (current) Address
void cleanup(Address *cur);


int main(int argc, char *argv[]) {
    Database *db = database_create();
    srand(time(NULL));

    char about[] = "This is a number conversion program, where one can choose the type of conversion and input "
            "option (normal, random) and save both original and converted arrays to the file. Version: v.0. "
            "Currently it supports converting binary numbers to decimal notation. Saving to a file is not "
            "yet supported.\n_____________________________\n-----------------------------";

    /*printf("%s\n", about);*/

    char option = '0';

    char info[] = "Usage: in the main shell, input the action[1], id[2] and input method [3] (optional).\n\n"
            "[1] Action - currently supported: g=get, s=set, d=delete, l=list, q=quit, i=info.\n"
            "[2] ID - a positive integer not exceeding 100\n"
            "[3] Input - currently supported: r=random. If input is left out, standard input will be used.\n\n"
            "Examples: (1) set 1 (2) list (3) s 2 r (4) delete 3 (5) set 2 random\n"
            "_____________________________\n-----------------------------";

    int id;
    int size;

    // User input processing from argv[] (1st implementation)

    if (argc > 1) {
        if (!strcmp(argv[1], "get") || !strcmp(argv[1], "g")) {
            printf("USER WANTS TO GET ELEMENTS\n");
            printf("THIS FUNCTION IS NOT YET SUPPORTED\n");
            printf("\n%s\n", info);
        } else if (!strcmp(argv[1], "set") || !strcmp(argv[1], "s")) {
            printf("USER WANTS TO SET ELEMENTS\n");
            printf("THIS FUNCTION IS NOT YET SUPPORTED\n");
            printf("\n%s\n", info);
        } else if (!strcmp(argv[1], "delete") || !strcmp(argv[1], "d")) {
            printf("USER WANTS TO DELETE ELEMENTS\n");
            printf("THIS FUNCTION IS NOT YET SUPPORTED\n");
            printf("\n%s\n", info);
        } else if (!strcmp(argv[1], "list") || !strcmp(argv[1], "l")) {
            printf("USER WANTS TO LIST ELEMENTS\n");
            goto LIST;
        } else {
            printf("INVALID PARAMETERS!\n\n");
            printf("%s\n", about);
            printf("%s\n", info);
        }
    }

    // User input processing from argv[] (2nd implementation)

    /*if (argc > 1) {*/

        /*id = 1;*/
        /*size = atoi(argv[1]);*/

        /*printf("SIZE %d\n", size);*/

        /*if (!parameter_valid(size)) {*/
            /*size = get_array_size();*/
        /*}*/

        /*goto SET;*/

    if (argc == 1) {
        printf("%s\n", about);
        printf("%s\n", info);
    }

    bool init = false;

    while (1) {
        if (init) printf("_____________________________\n-----------------------------\n");

        init = true;

        char **params = get_input();

        char action = (params)[0][0];

        if (params[1] != NULL) {
            id = atoi(params[1]);
        }

        if (params[2] != NULL) {
            option = params[2][0];
        }

        free_dup(&params);
        free(params);

        switch (action) {
            case 'g':
                database_get(db, id);
                break;
            case 's':; // An empty statement before a label
                Address *addr = &db->rows[id];
                if (addr->set) {
                    printf("Such entry already exists:\n");
                    database_get(db, id);
                    if (choice("Would you like to change it?")) {
                        database_delete(db, id);
                    } else {
                        break;
                    }
                }

                if (option != 'r') {
                    if (choice("Would you like to set maximum array size?")) {
                        size = get_array_size();
                    } else {
                        size = 0;
                    }
                } else {
                    size = get_array_size();
                }

            SET:; // An empty statement before a label
                Array *binary_array = malloc(sizeof(Array));
                if (binary_array == NULL) die();

                binary_array->size = size;

                if (option == 'r') {
                    random_binary(binary_array);
                } else {
                    get_array_elements(binary_array);
                }

                Array *decimal_array = binary_to_decimal(binary_array);

                if (choice("Would you like to save?")) {
                    database_set(db, id, binary_array, decimal_array);
                }
                break;
            case 'd':
                database_delete(db, id);
                break;
            case 'l':
            LIST:;
                database_list(db);
                break;
            case 'i':
                printf("_____________________________\n-----------------------------\n");
                printf("%s\n", info);
                init = false;
                break;
            case 'q':
                for (int i = 0; i < MAX_ROWS; i++) {
                    Address *cur = &db->rows[i];
                    if (cur->set) {
                        cleanup(cur);
                    }
                }
                free(db);

                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid action, only: g=get, s=set, d=delete, "
                               "l=list, q=quit, i=info\n");
        }

    }
}


void die() {
    char *message = "Memory error";
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}


bool choice(const char *message) {

    while (1) {
        printf("%s", message);
        printf(" [Y/n] ");
        char decision;

        if (scanf("%c", &decision) == 1 && (getchar() == '\n')) {

            switch (decision) {
                case 'y':
                case 'Y':
                    return true;
                case 'n':
                case 'N':
                    return false;
                default:
                    printf("Invalid action, only: Y=yes, N=no\n");
            }

        } else {
            printf("Invalid action, only: Y=yes, N=no\n");
            while (getchar() != '\n');
        }
    }
}


bool parameter_valid(int size) {
    if (size == 0) {
        printf("Array size cannot be a char, string or equal to 0");
        return false;
    }

    if (size > MAX_SIZE) {
        printf("Array size cannot exceed the maximum size - %d elements.", MAX_SIZE);
        return false;
    }

    if (size < 0) {
        printf("Array size cannot be negative");
        return false;
    }

    return true;
}


char **get_input() {

    int max_params = 3;
    char **params = NULL;
    params = calloc(max_params, max_params * sizeof(char *));
    if (params == NULL) die();

    char *pch;
    int count;

    int max_params_line = 100;
    char line[max_params_line];

    while (1) {
        printf("(main) > ");

        fgets(line, sizeof(line), stdin);

        count = 0;

        pch = strtok(line, " \n");
        while (pch != NULL) {

            if (count < 3) {
                // malloc() is used in strdup;
                params[count] = pch ? strdup(pch) : pch;
                if (!pch) die();
            }

            pch = strtok(NULL, " \n");
            count++;
        }
        /*
        Scan line by line till the end of input buffer
        while (line[strlen(line) - 1] != '\n') {
            fgets(line, sizeof(line), stdin);
            printf("still reading\n");
        }
         */

        // Validate argument count

        if (count == 0) {
            printf("The input is empty.\n");
            continue;
        }

        if (count > max_params) {
            printf("Too many arguments\n");
            free_dup(&params);
            continue;
        }

        // Validate action
        char *all_actions = "g,s,d,l,i,q,get,set,delete,list,info,quit";
        if (strstr(all_actions, params[0]) == NULL) {
            printf("Such action does not exist\n");
            free_dup(&params);
            continue;
        }


        char action = params[0][0];

        char *actions = "gsdliq";
        if (strchr(actions, action) == NULL) {
            printf("Such action does not exist\n");
            free_dup(&params);
            continue;
        }


        if (count == 1) {
            char *actions = "gsd";
            if (strchr(actions, action) != NULL) {
                printf("ID is not submitted\n");
                free_dup(&params);
                continue;
            }
        }

        // Validate id
        if (count > 1) {

            char *one_args = "liq";
            if (strchr(one_args, action) != NULL) {
                printf("Too much arguments for this action\n");
                free_dup(&params);
                continue;
            }

            int id = atoi(params[1]);

            // id being equal to 0 in condition
            // below also validates from char input
            if (id <= 0 || id > MAX_SIZE) {
                printf("ID should be a positive integer less or equal to 100.\n");
                free_dup(&params);
                continue;
            }
        }

        // Validate option
        if (count > 2) {

            char *all_options = "r,random,rand";
            if (strstr(all_options, params[2]) == NULL) {
                printf("Such option does not exist\n");
                free_dup(&params);
                continue;
            }

            char option = params[2][0];

            char *options = "r";
            if (strchr(options, option) == NULL) {
                printf("Such option does not exist\n");
                free_dup(&params);
                continue;
            }
        }

        break;
    }
    return params;

}


void free_dup(char ***params) {
    char **it;
    for (it = *params; it && *it; ++it) {
        free(*it);
    }
}


int get_array_size() {
    int size;

    while (1) {
        printf("Enter maximum array size (how many numbers it will hold), not exceeding %d. > ", MAX_SIZE);
        if ((scanf("%d", &size) == 1) && (size <= MAX_SIZE) && (size > 0) && (getchar() == '\n')) {
            break;
        } else {

            printf("Please make sure that the size does not exceed the maximum limit (100),"
                           " is a positive integer\n");
            while (getchar() != '\n');
        }
    }
    return size;
}

void get_array_elements(Array *binary_array) {
    int size = binary_array->size;

    if (size == 0) {
        size = MAX_SIZE;
    }
    printf("Enter an array (max size: %d) of binary numbers, separated by a space. Maximum "
                   "number of numerals in each number is %d:\n", size, MAX_NUMBER_SIZE);

    int *array = NULL;
    array = malloc(size * sizeof(int));
    if (array == NULL) {
        die();
    }


    int *error_array = NULL;
    error_array = malloc(size * sizeof(int));
    if (error_array == NULL) {
        die();
    }

    int i;
    int count;
    bool too_much;
    int str_error_size;

    char line[MAX_DATA];
    char *newline;
    char *pch;

    int length;

    while (1) {
        printf("> ");
        str_error_size = 0;
        too_much = false;

        fgets(line, sizeof(line), stdin);
        i = 0;

        count = 0;

        newline = strchr(line, '\n');
        if (newline) {
            *newline = 0;
        }

        pch = strtok(line, " ,.-\n");
        while (pch != NULL) {

            if (count >= size) {
                too_much = true;
                break;
            }

            length = strlen(pch);

            if (length > MAX_NUMBER_SIZE || count == MAX_SIZE) {
                str_error_size += 1;
                break;
            }

            for (i = 0; i < length; i++) {
                if (!isdigit(pch[i])) {
                    str_error_size += 1;
                    break;
                }
            }

            array[count++] = atoi(pch);

            pch = strtok(NULL, " ,.-");

        }


        if (count == 0) {
            str_error_size += 1;
        }

        array = realloc(array, (count) * sizeof(int));

        int error_size = 0;

        for (i = 0; i < count; i++) {
            error_array[i] = 0;
        }

        for (i = 0; i < count; i++) {
            if (!is_binary(array[i])) {
                error_array[i] = array[i];
                error_size += 1;
            }
        }

        char *error_head;
        char *error_tail;
        char *try_again = "Try again.";

        if (str_error_size > 0) {
            printf("Please enter appropriate binary numbers (maximum number of numerals in "
                           "each number is %d).\n", MAX_NUMBER_SIZE);
            printf("%s\n", try_again);
        } else if (too_much) {
            printf("Entered numbers exceed the size of the array. Please enter no more than "
                           "%d numbers.\n", size);
        } else if (error_size > 0) {
            if (error_size > 1) {
                error_head = "Numbers ";
                error_tail = "are not binary. ";
            } else {
                error_head = "Number ";
                error_tail = "is not binary. ";
            }
            printf("%s", error_head);
            unique_errors(error_array, i);
            printf("%s", error_tail);
            printf("%s\n", try_again);
        } else {
            free(error_array);
            break;
        }
    }

    binary_array->size = count;
    binary_array->elements = malloc(count * sizeof(int));
    if (binary_array->elements == NULL) die();

    for (i = 0; i < count; i++) {
        binary_array->elements[i] = array[i];
    }

    free(array);

}


void unique_errors(int *errors, int size) {

    int i;
    int j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < i; j++) {
            if (errors[i] == errors[j]) {
                break;
            }
        }

        if (i == j && errors[i] != 0) {
            // No duplicate element found between index 0 to i
            printf("%d ", errors[i]);
        }
    }
}

Database *database_create() {
    Database *db = malloc(sizeof(Database));
    if (db == NULL) die();

    int i = 0;
    for (i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize it
        Address addr = {.id = i, .set = 0};
        // then just assign it
        db->rows[i] = addr;
    }
    return db;
}

void database_set(Database *db, int id, Array *binary_array, Array *decimal_array) {
    Address *addr = &db->rows[id];

    addr->binary_array = binary_array;
    addr->decimal_array = decimal_array;
    addr->set = 1;

    printf("Successfully saved, ID = %d\n", id);
}


void database_get(Database *db, int id) {
    Address *addr = &db->rows[id];
    if (addr->set) {
        address_print(addr);
    } else {
        printf("ID is not set\n");
    }
}

void database_list(Database *db) {
    int i = 0;
    int count = 0;

    for (i = 0; i < MAX_ROWS; i++) {
        Address *cur = &db->rows[i];
        if (cur->set) {
            count += 1;
            address_print(cur);
        }
    }

    if (count == 0) {
        printf("No entries.\n");
    }
}

void address_print(Address *addr) {
    int i;
    int size = addr->binary_array->size;
    printf("%d. ", addr->id);
    printf("Binary: [");
    for (i = 0; i < size; i++) {
        printf("%d", addr->binary_array->elements[i]);
        if (i != size - 1) {
            printf(" ");
        }
    }
    printf("] Decimal: [");
    for (i = 0; i < size; i++) {
        printf("%d", addr->decimal_array->elements[i]);
        if (i != size - 1) {
            printf(" ");
        }
    }
    printf("]");

    printf("\n");
}

void database_delete(Database *db, int id) {
    if (db->rows[id].set == 0) {
        printf("No such entry in database\n");
    } else {
        if (choice("Do you really want to delete this entry?")) {
            Address *cur = &db->rows[id];
            cleanup(cur);

            cur->set = 0;
            printf("Successfully deleted\n");
        }
    }
}

void cleanup(Address *cur) {
    free(cur->binary_array->elements);
    free(cur->decimal_array->elements);
    free(cur->binary_array);
    free(cur->decimal_array);
}
