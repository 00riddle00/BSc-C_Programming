/*==============================================================================
 |
 |  Assignment:  Homework #1, #2
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO1, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Programming Basics
 |         Date:  December 20th, 2017
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |   To Compile:  gcc -Wall -g -lm -std=gnu11 namu_darbas.c -o namu_darbas
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
 |       TODOS:   add saving to a file
 |
 | Version
 | updates:     Currently this is the intial version
 |
 +===========================================================================*/


#include <stdio.h>
#include <stdlib.h>

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
#define MAX_PARAMS 2

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
    Car *car;
} Address;

// database
typedef struct {
    Address rows[MAX_ROWS];
} Database;

typedef struct {
    int count;
    int valid;
    char** params;
} Input;

void get_input(Input* input);

int valid_input(Input* input);

void clear_input(Input* input);

// prompt for user input ([Y/n])
//
// ::params: message - prompt message
// ::return: (decision (yes or no))
int choice(const char *message);

// description
void get_car(Car *car);

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

// prints out the error message and exits.
// use only in case of memory errors.
void die();


int main(int argc, char *argv[]) {
    Database *db = database_create();

    char about[] = "This is a car database program, where one can perform get, list, create, edit and delete "
            "operations. The database is loaded from and saved to the binary file. Version: v.0";

    char info[] = "Usage: in the main shell, input the Action[1] and ID[2].\n\n"
            "[1] Action - g=get, l=list, s=set, d=delete, c=clear database, q=quit, i=info.\n"
            "[2] ID - a positive integer not exceeding 100. Only get, set and delete operations\n"
            "require ID parameter.\n"
            "Examples: (1) get 1 (get 1st element) (2) l (list elements) (3) set 2 (set 2nd element)";

    char* separator = "---------------------------------------------------";

    // shows whether the were command line arguments to a program
    int cmd = 0;

    // id for database entries
    int id;

    // initialize input variable
    Input* input = (Input*) malloc(sizeof(Input));
    input->params = malloc(MAX_PARAMS * sizeof(char *));
    input->count = 0;
    input->valid = 0;

    // print info about the program
    printf("%s\n\n", about);
    printf("%s\n", separator);
    printf("%s\n\n", info);

    // process command line input
    if (argc > 1) {
        cmd = 1;
        input->params[0] = argv[1];
        input->count++;

        if (argc > 2) {
            input->params[1] = argv[2];
            input->count++;
        }
        
        if (argc > 3) {
            printf("Too many arguments\n");
            cmd = 0;
        }
    }

    // main control loop
    while (1) {
        printf("%s\n", separator);

        if (cmd) {
            cmd = 0;
            if (!valid_input(input)) {
                clear_input(input);
                continue;
            }
        } else {
            clear_input(input);
            get_input(input);
        }

        char action = (input->params)[0][0];

        if (input->params[1] != NULL) {
            id = atoi(input->params[1]);
        }

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

                if (choice("Would you like to save?")) {
                    database_set(db, id, car);
                }
                break;
            case 'd':
                database_delete(db, id);
                break;
            case 'l':
                database_list(db);
                break;
            case 'c':
                database_clear(db);
                break;
            case 'i':
                printf("\n%s\n", separator);
                printf("%s\n\n", info);
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
                printf("Invalid action, only: g=get, s=set, d=delete, l=list, q=quit, i=info\n");
        }

    }
}

void get_input(Input* input) {

    char *pch;

    int max_params_line = 100;
    char line[max_params_line];

    while (1) {
        printf("[enter \"i\" for info] main shell > ");

        fgets(line, sizeof(line), stdin);

        pch = strtok(line, " \n");
        while (pch != NULL) {

            if (input->count < MAX_PARAMS + 1) {
                // malloc() is used in strdup;
                input->params[input->count] = pch ? strdup(pch) : pch;
                if (!pch) die();
            }

            pch = strtok(NULL, " \n");
            input->count++;
        }

        if (valid_input(input)) {
            input->valid = 1;
            break;
        } else {
            clear_input(input);
        }
    }
}

int valid_input(Input* input) {

    // Validate argument count
    int count = input->count;

    if (count == 0) {
        printf("The input is empty.\n");
        return 0;
    }

    if (count > MAX_PARAMS) {
        printf("Too many arguments\n");
        return 0;
    }


    // Validate action
    char *all_actions = "g,s,d,l,c,i,q,get,set,delete,list,clear,info,quit";
    if (strstr(all_actions, input->params[0]) == NULL) {
        printf("Such action does not exist\n");
        return 0;
    }


    char action = input->params[0][0];

    char *actions = "gsdlciq";
    if (strchr(actions, action) == NULL) {
        printf("Such action does not exist\n");
        return 0;
    }


    if (count == 1) {
        char *actions = "gsd";
        if (strchr(actions, action) != NULL) {
            printf("ID is not submitted\n");
            return 0;
        }
    }


    // Validate id
    if (count > 1) {

        char *one_args = "licq";
        if (strchr(one_args, action) != NULL) {
            printf("Too much arguments for this action\n");
            return 0;
        }

        int id = atoi(input->params[1]);

        // id being equal to 0 in condition
        // below also validates from char input
        if (id <= 0 || id > MAX_SIZE) {
            printf("ID should be a positive integer less or equal to 100.\n");
            return 0;
        }
    }

    return 1;
}

void clear_input(Input* input) {
    for (int i = 0; i < MAX_PARAMS; ++i) {
        input->params[i] = NULL;
    }
    input->valid = 0;
    input->count = 0;
}


int choice(const char *message) {

    while (1) {
        printf("%s", message);
        printf(" [Y/n] ");
        char decision;

        if (scanf("%c", &decision) == 1 && getchar() == '\n') {

            switch (decision) {
                case 'y':
                case 'Y':
                    return 1;
                case 'n':
                case 'N':
                    return 0;
                default:
                    printf("Invalid action, only: Y=yes, N=no\n");
            }

        } else {
            printf("Invalid action, only: Y=yes, N=no\n");
            while (getchar() != '\n');
        }
    }
}


void get_car(Car *car) {
    car->make = malloc(30);
    car->model= malloc(30);
    
    int temp;
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

void database_set(Database *db, int id, Car *car) { 
    Address *addr = &db->rows[id];

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


void die() {
    char *message = "Memory error";
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}


