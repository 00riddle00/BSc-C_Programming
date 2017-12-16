/*==============================================================================
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

#include "dbg.h"


#define MAX_SIZE 100
#define MAX_DATA 1536
#define MAX_NUMBER_SIZE 10
#define MAX_ROWS 100
#define MAX_LINE 100

//2. Automobilis (firmos pavadinimas, modelio pavadinimas, pagaminimo metai, automobilio kaina).
typedef struct {
    char *make;
    char *model;
    int year;
    int price;
} Car;

// database address ('set' - whether is set (exists) or not)
typedef struct {
    int id;
    int set;
    /*Array *decimal_array;*/
    /*Array *binary_array;*/
    Car *car;
} Address;

// database
typedef struct {
    Address rows[MAX_ROWS];
} Database;


// prints out the error message and exits.
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


// description
void get_car(Car *car);

// from array of errors, remove duplicates
// and print the error values (non-binary number)
//
// ::params: array - error array
// ::params: size - size of error array
void unique_errors(int *array, int size);


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
void database_set(Database *db, int id, Car *car); 

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


// description
void database_clear(Database *db);

// [1] free two Array's (struct) elements in Address (struct)
// [2] free two Array's (struct) in Address (struct)
//
// ::params: cur - (current) Address
void cleanup(Address *cur);


int main(int argc, char *argv[]) {
    Database *db = database_create();
    srand(time(NULL));

    char about[] = "This is a car database program, where one can perform get, list, create, edit and delete "
            "operations. The database is loaded from and saved to the binary file. Version: v.0"
            "\n-------------------------------";

    char info[] = "Usage: in the main shell, input the Action[1] and ID[2].\n\n"
            "[1] Action - g=get, l=list, s=set, d=delete, c=clear database, q=quit, i=info.\n"
            "[2] ID - a positive integer not exceeding 100. Only get, set and delete operations\n"
            "require ID parameter.\n"
            "Examples: (1) get 1 (get 1st element) (2) l (list elements) (3) set 2 (set 2nd element)\n"
            "_____________________________\n-----------------------------";

    int id;

    // User input processing from argv[] (1st implementation)

    if (argc > 1) {
        char action = argv[1][0];

        switch (action) {
            case 'g':
                printf("USER WANTS TO GET ELEMENTS\n");
                printf("THIS FUNCTION IS NOT YET SUPPORTED\n");
                printf("\n%s\n", info);
                break;
            case 'l':
                printf("USER WANTS TO LIST ELEMENTS\n");
                goto LIST;
                break;
            case 's':
                printf("USER WANTS TO SET ELEMENTS\n");
                printf("THIS FUNCTION IS NOT YET SUPPORTED\n");
                printf("\n%s\n", info);
                break;
            case 'd':
                printf("USER WANTS TO DELETE ELEMENTS\n");
                printf("THIS FUNCTION IS NOT YET SUPPORTED\n");
                printf("\n%s\n", info);
                break;
            case 'c':
                printf("USER WANTS TO CLEAR DATABASE\n");
                printf("THIS FUNCTION IS NOT YET SUPPORTED\n");
                printf("\n%s\n", info);
                break;

            default:
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
            /*printf("Too much params");*/
            /*option = params[2][0];*/
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

                Car *car = malloc(sizeof(Car));
                if (car == NULL) die();
                get_car(car);

            SET:; // An empty statement before a label

                if (choice("Would you like to save?")) {
                    database_set(db, id, car);
                }
                break;
            case 'd':
                database_delete(db, id);
                break;
            case 'l':
            LIST:;
                database_list(db);
                break;
            case 'c':
                database_clear(db);
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

        if (scanf("%c", &decision) == 1 && getchar() == '\n') {

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
        char *all_actions = "g,s,d,l,c,i,q,get,set,delete,list,clear,info,quit";
        if (strstr(all_actions, params[0]) == NULL) {
            printf("Such action does not exist\n");
            free_dup(&params);
            continue;
        }


        char action = params[0][0];

        char *actions = "gsdlciq";
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

            char *one_args = "licq";
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

void get_car(Car *car) {
    car->make = malloc(30);
    car->model= malloc(30);
    
    int temp;
    char input[MAX_LINE];
    int error;

    while (1) {
        printf("Enter make > ");
        memset(car->make,0,sizeof(car->make));

        if (scanf("%[^\n]%*c", car->make) == 1) {

            error = 0;

            for (int i = 0; i < 10; i++) {
                if(isdigit(car->make[i])) {
                    error = 1;
                    break;
                }
            }

            if(error) {
                printf("Car make cannot contain numbers\n");
                continue;
            }

            break;

        } else {
            while((temp=getchar()) != EOF && temp != '\n');
            printf("Please make sure that make is normal format\n");
        }
    }

    while (1) {
        printf("Enter model > ");
        if (scanf("%[^\n]%*c", car->model) == 1) {
            break;
        } else {
            while((temp=getchar()) != EOF && temp != '\n');
            printf("Please make sure that model is normal format\n");
        }
    }

    // FIXME does not eat newline after no input and return key is pressed
    while (1) {
        printf("Enter year > ");
        if (scanf("%d", &car->year) == 1 && car->year > 1920 && car->year < 2018) {
            break;
        } else {
            while((temp=getchar()) != EOF && temp != '\n');
            printf("Please make sure that year is normal format\n");
        }
    }

    // FIXME does not eat newline after no input and return key is pressed
    while (1) {
        printf("Enter price > ");
        if (scanf("%d", &car->price) == 1 && car->price > 0) {
            break;
        } else {
            while((temp=getchar()) != EOF && temp != '\n');
            printf("Please make sure that price is normal format\n");
        }
    }

    while (getchar() != '\n');

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

void database_set(Database *db, int id, Car *car) { // Array *binary_array, Array *decimal_array) {
    Address *addr = &db->rows[id];

    /*addr->binary_array = binary_array;*/
    /*addr->decimal_array = decimal_array;*/
    addr->car = car;
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

    printf("%d. ", addr->id);

    printf("%s %s %d %d", addr->car->make, addr->car->model, addr->car->year, addr->car->price);

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


void database_clear(Database *db) {
    int i = 0;
    int count = 0;

    if (choice("Do you really want to clear the entire database?")) {

        for (i = 0; i < MAX_ROWS; i++) {
            Address *cur = &db->rows[i];
            if (cur->set) {
                cleanup(cur);
                cur->set = 0;
                count += 1;
            }
        }

        if (count) {
            printf("Database has been successfully cleared.\n");
        } else {
            printf("Database has no entries. Nothing to clear.\n");
        }
    }
}


void cleanup(Address *cur) {
    free(cur->car);
}

