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
 |  Description:  A car database program, where one can perform get, list, 
 |                create, edit, delete and clear operations. There are four fields
 | 				  for each car entry: (1) Make (2) Model (3) Year (4) Price. The 
 | 			      database is loaded from and saved to the binary file. The user
 | 				  can also perform sorting (ascending, descending) actions by each
 | 			      of the four fields, and also filtering by each field. There are 
 | 			      four filtering options: (1) Value is equal (2) Value contains 
 | 				  (3) Value is not equal (4) Value does not contain. After sorting
 | 			      or filtering, the changed database output is displayed to the 
 | 			      screen, however, is not written to the database, hence the order 
 | 				  remains the same before sort or filter action. Each time the 
 | 				  program runs, the log entry is created in ./log.txt file, with
 | 				  the info about the beginning of the program and how much time did
 | 				  it run.
 |
 |  Constraints:  
 |                
 |	    Input:    Command line input by user
 |
 |	    Output:   Prompt messages, validation errors and final results
 |                are displayed one per line to the standard output.
 |
 |  Known bugs:   
 |                
 |       TODOS:   (1) Move sorting, filtering, and binary file processing 
 | 				  functions to separate modules. 
 | 				  (2) Use dynamic memory instead of static for data types.
 | 				  (3) Implement logging to a file (./log.txt)
 | 				  (4) Add unit tests
 |
 | Version
 | updates:       Version 1.4 
 |
 +===========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

#include "dbg.h"
/*#include "binary_file.h"*/
/*#include "sorting.h"*/
/*#include "filter.h"*/
#include "lib_riddle.h"

#define MAX_ID 100
#define MAX_ROWS 100
#define MAX_LINE 100
#define MAX_TEXT_LENGTH 30
#define MAX_PARAMS 2
#define LATEST_YEAR 2018
#define EARLIEST_YEAR 1920
#define CHUNK_SIZE 10

// car (make, model, year of making, car price)
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
    char car_make[10];
    char car_model[10];
    int car_year;
    int car_price;
} Address;

// database
typedef struct {
    Address** rows;
    int size;
    int capacity;
} Database;


// static database
typedef struct {
    Address rows[MAX_ROWS];
    /*int size;*/
} StaticDatabase;


// input structure
typedef struct {
    int count;
    int valid;
    char** params;
} Input;

// connection structure
// has a pointer to file and a pointer to database
typedef struct {
    FILE *file;
    StaticDatabase *db;
} Connection;

// ::params: input - input structure is modified
void get_input(Input* input);

// ::params: input - input structure 
// ::return: 1 if input is valid, else 0
int valid_input(Input* input);

// set input value and input count to 0, nullify pointers 
// inside input->params
//
// ::params: input - input structure is modified
void clear_input(Input* input);

// prompt user to enter a new database entry (car) 
// ::params: car object is modified
void get_car(Car *car);


// open database from file. If file does not
// exist, return an error and exit. If database is failed
// to load, prompt user to create a new database
//
// ::params: filename - name of a file
// ::return: connection struct
Connection *database_open(const char* filename);


// allocate space and create database
// (initialize Address structs)
//
// ::params: conn - Connection struct
void database_create(Connection* conn);

// write current state of database to a file
//
// ::params: conn - Connection struct
void database_write(Connection *conn);


// set Address struct in database
//
// ::params: db - Database
// ::params: id - entry id (user input)
// ::params: car - car struct
void database_set(StaticDatabase* db, int id, Car *car);

// get address from database
//
// ::params: conn - connection struct
// ::params: id - entry id (user input)
void database_get(Connection *conn, int id);

// get address from database
//
// ::params: db - Database
// ::params: reverse - whether to print in 
// reverse order (used in sorting)
void database_list(StaticDatabase* db, int reverse);

// print address from database
//
// ::params: addr - Address
void address_print(Address *addr);

// delete address from database
//
// ::params: conn - Connection struct
// ::params: id - entry id (user input)
void database_delete(Connection* conn, int id);


// clear database
// 
// ::params: conn - Connection struct
void database_clear(Connection *conn);

// close connection to a file, and free
// database (conn->db) as well as connection (conn) structs
// 
// ::params: conn - Connection struct
void database_close(Connection *conn);




/*Database* deserialize(Connection* conn) {*/

    /*[>int size = conn->db->size;<]*/
    /*int size = 6;*/
    /*int times = floor((size / CHUNK_SIZE) + 0.5);*/

    /*Database* db = malloc(sizeof(Database));*/
    /*db->capacity = CHUNK_SIZE * times;*/
    /*// FIXME ar geras sizeof adress?*/
    /*db->rows = malloc(db->capacity * sizeof(Address*));*/
    /*db->size = 0;*/

    /*for (int i = 0; i < size; i++) {*/
        /*Address *cur = &conn->db->rows[i];*/
            /*if (cur->set) {*/
                /*debug("car make %s", cur->car_make);*/
                /*db->rows[db->size++] = cur;*/
            /*}*/
    /*}*/
    /*return db;*/
/*}*/






/*void filter_by_make(Database* db, int type, char* value) {*/

    /*switch(type) {*/
        /*case 1:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*if (strcmp(cur->car_make, value) != 0) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
        /*case 2:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*if (strstr(cur->car_make, value) == NULL) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
        /*case 3:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*if (strcmp(cur->car_make, value) == 0) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
        /*case 4:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*if (strstr(cur->car_make, value) != NULL) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
    /*}*/
/*}*/

/*void filter_by_model(Database* db, int type, char* value) {*/

    /*switch(type) {*/
        /*case 1:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*if (strcmp(cur->car_model, value) != 0) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
        /*case 2:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*if (strstr(cur->car_model, value) == NULL) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
        /*case 3:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*if (strcmp(cur->car_model, value) == 0) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
        /*case 4:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*if (strstr(cur->car_model, value) != NULL) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
    /*}*/
/*}*/


/*void filter_by_year(Database* db, int type, char* value) {*/

    /*char year_string[MAX_TEXT_LENGTH];*/

    /*switch(type) {*/
        /*case 1:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*sprintf(year_string, "%d", cur->car_year);*/
                    /*if (strcmp(year_string, value) != 0) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
        /*case 2:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*sprintf(year_string, "%d", cur->car_year);*/
                    /*if (strstr(year_string, value) == NULL) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
        /*case 3:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*sprintf(year_string, "%d", cur->car_year);*/
                    /*if (strcmp(year_string, value) == 0) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
        /*case 4:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*sprintf(year_string, "%d", cur->car_year);*/
                    /*if (strstr(year_string, value) != NULL) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
    /*}*/
/*}*/


/*void filter_by_price(Database* db, int type, char* value) {*/

    /*char price_string[MAX_TEXT_LENGTH];*/

    /*switch(type) {*/
        /*case 1:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*sprintf(price_string, "%d", cur->car_price);*/
                    /*if (strcmp(price_string, value) != 0) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
        /*case 2:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*sprintf(price_string, "%d", cur->car_price);*/
                    /*if (strstr(price_string, value) == NULL) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
        /*case 3:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*sprintf(price_string, "%d", cur->car_price);*/
                    /*if (strcmp(price_string, value) == 0) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
        /*case 4:*/
            /*for (int i = 0; i < MAX_ROWS; i++) {*/
                /*Address *cur = &db->rows[i];*/
                /*if (cur->set) {*/
                    /*sprintf(price_string, "%d", cur->car_price);*/
                    /*if (strstr(price_string, value) != NULL) {*/
                        /*cur->set = 0;*/
                    /*} */
                /*}*/
            /*}*/
            /*break;*/
    /*}*/
/*}*/








/*Database* sort_lex_by_make(Database* db, int first, int last)*/
/*{*/

    /*int i, j;*/
    /*Address temp;*/

    /*for (i = first; i < last; ++i)*/

        /*for (j = i + 1; j < last + 1; ++j) {*/

            /*if (strcmp(db->rows[i].car_make, db->rows[j].car_make) > 0) {*/
                /*temp = db->rows[i];*/
                /*db->rows[i] = db->rows[j];*/
                /*db->rows[j] = temp;*/
            /*}*/
        /*}*/

    /*return db;*/
/*}*/


/*Database* sort_lex_by_model(Database* db, int first, int last)*/
/*{*/

    /*int i, j;*/
    /*Address temp;*/

    /*for (i = first; i < last; ++i)*/

        /*for (j = i + 1; j < last + 1; ++j) {*/

            /*if (strcmp(db->rows[i].car_model, db->rows[j].car_model) > 0) {*/
                /*temp = db->rows[i];*/
                /*db->rows[i] = db->rows[j];*/
                /*db->rows[j] = temp;*/
            /*}*/
        /*}*/

    /*return db;*/
/*}*/

/*Database* sort_by_year(Database* db, int first, int last)*/
/*{*/

    /*Address temp;*/
    /*int pivot, j, i;*/

    /*if (first < last) {*/
        /*pivot = first;*/
        /*i = first;*/
        /*j = last;*/

        /*while (i < j) {*/
            /*while (*/
                /*db->rows[i].car_year <= db->rows[pivot].car_year && i < last) {*/
                /*i++;*/
            /*}*/
            /*while (db->rows[j].car_year > db->rows[pivot].car_year) {*/
                /*j--;*/
            /*}*/
            /*if (i < j) {*/
                /*temp = db->rows[i];*/
                /*db->rows[i] = db->rows[j];*/
                /*db->rows[j] = temp;*/
            /*}*/
        /*}*/

        /*temp = db->rows[pivot];*/
        /*db->rows[pivot] = db->rows[j];*/
        /*db->rows[j] = temp;*/

        /*sort_by_year(db, first, j - 1);*/
        /*sort_by_year(db, j + 1, last);*/
    /*}*/
    /*return db;*/
/*}*/

/*Database* sort_by_price(Database* db, int first, int last)*/
/*{*/

    /*Address temp;*/
    /*int pivot, j, i;*/

    /*if (first < last) {*/
        /*pivot = first;*/
        /*i = first;*/
        /*j = last;*/

        /*while (i < j) {*/
            /*while (*/
                /*db->rows[i].car_price <= db->rows[pivot].car_price && i < last) {*/
                /*i++;*/
            /*}*/
            /*while (db->rows[j].car_price > db->rows[pivot].car_price) {*/
                /*j--;*/
            /*}*/
            /*if (i < j) {*/
                /*temp = db->rows[i];*/
                /*db->rows[i] = db->rows[j];*/
                /*db->rows[j] = temp;*/
            /*}*/
        /*}*/

        /*temp = db->rows[pivot];*/
        /*db->rows[pivot] = db->rows[j];*/
        /*db->rows[j] = temp;*/

        /*sort_by_price(db, first, j - 1);*/
        /*sort_by_price(db, j + 1, last);*/
    /*}*/
    /*return db;*/
/*}*/


void perform_action(int action, StaticDatabase* db) {
    int field; 
    int type;
    char* value;
    StaticDatabase* temp_db;

    switch(action) {
        case 1:
            printf("By which field would you like to filter? (enter a number)\n");
            printf("(1) Make\n");
            printf("(2) Model\n");
            printf("(3) Year\n");
            printf("(4) Price\n");

            field = get_num_interval("(Enter a number) > ", "Such option does not exist", 1, 4);

            printf("How would you like to filter?\n");
            printf("(1) Entry is equal to the given value\n");
            printf("(2) Entry contains the given value\n");
            printf("(3) Entry is not equal to the given value\n");
            printf("(4) Entry does not contain the given value\n");

            type = get_num_interval("(Enter a number) > ", "Such option does not exist", 1, 4);

            printf("Please enter a value to be filtered by\n");
            value = malloc(sizeof(char) * MAX_TEXT_LENGTH);
            value = get_text("(Enter a value) > ", value);

            temp_db = malloc(sizeof(Database));
            memcpy(&(temp_db->rows), &(db->rows), sizeof(db->rows));

            /*switch(field) {*/
                /*case 1:*/
                    /*filter_by_make(temp_db, type, value);*/
                    /*break;*/
                /*case 2:*/
                    /*filter_by_model(temp_db, type, value);*/
                    /*break;*/
                /*case 3:*/
                    /*filter_by_year(temp_db, type, value);*/
                    /*break;*/
                /*case 4:*/
                    /*filter_by_price(temp_db, type, value);*/
                    /*break;*/
     /*       }*/
			database_list(temp_db, 0);
            break;

        case 2:
            printf("By which field would you like to sort? (enter a number)\n");
            printf("(1) Make\n");
            printf("(2) Model\n");
            printf("(3) Year\n");
            printf("(4) Price\n");

            field = get_num_interval("(Enter a number) > ", "Such option does not exist", 1, 4);

            printf("How would you like to sort?\n");
            printf("(1) Ascending order\n");
            printf("(2) Descending order\n");

            type = get_num_interval("(Enter a number) > ", "Such option does not exist", 1, 2);

            int reverse = (type == 1) ? 0 : 1;

            temp_db = malloc(sizeof(Database));
            memcpy(&(temp_db->rows), &(db->rows), sizeof(db->rows));

/*            switch(field) {*/
                /*case 1:*/
                    /*sort_lex_by_make(temp_db, 0, 99);*/
                    /*break;*/
                /*case 2:*/
                    /*sort_lex_by_model(temp_db, 0, 99);*/
                    /*break;*/
                /*case 3:*/
                    /*sort_by_year(temp_db, 0, 99);*/
                    /*break;*/
                /*case 4:*/
                    /*sort_by_price(temp_db, 0, 99);*/
                    /*break;*/
/*            }*/
            database_list(temp_db, reverse);
            break;
    }

}


int main(int argc, char *argv[]) {
    if (argc < 2) die ("USAGE: test <dbfile> <action> [action params]");

    char* filename = argv[1];
    Connection* conn = database_open(filename);
    /*Database* db = deserialize(conn);*/
    /*debug("DB: %d", db->size);*/
    /*int id = 0;*/

    char* about = "This is a car database program, where one can perform get, list, create, edit and delete "
            "operations. The database is loaded from and saved to the binary file. Version: v.0";

    char* info = malloc(350 * sizeof(char*));
    sprintf(info, "Usage: in the main shell, input the Action[1] and ID[2].\n\n[1] Action - g=get, l=list, \
s=set, d=delete, c=clear database, q=quit, i=info.\n[2] ID - a positive integer not exceeding %d. Only get,\
set and delete operations\nrequire ID parameter.\nExamples: (1) get 1 (get 1st element) (2) l (list elements)\
(3) set 2 (set 2nd element)", MAX_ID);

    char* separator = "---------------------------------------------------";

    // shows whether the were command line arguments to a program
    int cmd = 0;

    // id for database entries
    int id;

    

    /*// initialize input variable*/
    Input* input = (Input*) malloc(sizeof(Input));
    input->params = malloc(MAX_PARAMS * sizeof(char *));
    input->count = 0;
    input->valid = 0;

    // print info about the program
    printf("%s\n\n", about);
    printf("%s\n", separator);
    printf("%s\n\n", info);

    // process input from argv
    if (argc > 2) {
        cmd = 1;
        input->params[0] = argv[2];
        input->count++;

        if (argc > 3) {
            input->params[1] = argv[3];
            input->count++;
        }
        
        if (argc > 4) {
            printf("Too many arguments\n");
            cmd = 0;
        }
    }

    // main control loop
    while (1) {
        printf("%s\n", separator);

        // in case of argv input
        if (cmd) {
            cmd = 0;
            if (!valid_input(input)) {
                clear_input(input);
                continue;
            }
        // else get input from user
        } else {
            clear_input(input);
            get_input(input);
        }

        // setting action from input
        char action = (input->params)[0][0];

        // setting id from input
        if (input->params[1] != NULL) {
            id = atoi(input->params[1]);
        }

        switch (action) {
            case 'a':
                printf("What action would you like to perform? (enter a number)\n");
                printf("(1) Filter\n");
                printf("(2) Sort\n");

                StaticDatabase *db = conn->db;
                action = get_num_interval("(Enter a number) > ", "Such option does not exist", 1, 2);
                perform_action(action, db);
                break;
            case 'g':
                database_get(conn, id);
                break;
            case 's':; // An empty statement before a label
                /*Address *addr = &conn->db->rows[db->size];*/
                /*debug("HERE");*/
                /*debug("%d", db->size);*/

                /*for (int i = 0; i < db->size; i++) {*/
				for (int i = 0; i < MAX_ROWS; i++) {
                    Address *cur = &conn->db->rows[i];
                    if (cur->id == id) {

                        if (cur->set) {
                            printf("Such entry already exists:\n");
                            database_get(conn, id);
                            if (choice("Would you like to change it?")) {
                                database_delete(conn, id);
                                database_write(conn);
                            } else {
                                break;
                            }
                        }
                    }
                }

				debug("Here now");

                Car *car = malloc(sizeof(Car));
                if (car == NULL) die("Memory error");
                get_car(car);

                if (choice("Would you like to save?")) {
                    database_set(conn->db, id, car);
					database_write(conn);
                }
                break;
            case 'd':
                database_delete(conn, id);
                database_write(conn);
                break;
            case 'l':
				database_list(conn->db, 0);
                break;
            case 'c':
                database_clear(conn);
                break;
            case 'i':
                printf("\n%s\n", separator);
                printf("%s\n\n", info);
                break;
            case 'q':
                for (int i = 0; i < MAX_ROWS; i++) {
                    Address *cur = &conn->db->rows[i];
                    if (cur->set) {
                        /*free(cur->car->make);*/
                        /*free(cur->car->model);*/
                        /*free(cur->car);*/
                    }
                }
                /*free(db);*/
                database_close(conn);
                /*free(info);*/
                /*free(input->params);*/
                /*for (int i = 0; i < 2; ++i) {*/
                    /*free(input->params[i]);*/
                /*}*/
                /*free(input);*/

                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid action, only: g=get, s=set, d=delete, l=list, q=quit, i=info\n");
        }

    }
}

void get_input(Input* input) {

    char *pch;

    char line[MAX_LINE];

    while (1) {
        printf("[enter \"i\" for info] main shell > ");

        fgets(line, sizeof(line), stdin);

        pch = strtok(line, " \n");
        while (pch != NULL) {

            if (input->count < MAX_PARAMS + 1) {
                // malloc() is used in strdup;
                input->params[input->count] = pch ? strdup(pch) : pch;
                if (!pch) die("Memory error");
            }

            pch = strtok(NULL, " \n");
            input->count++;
        }

        // break if input is valid
        if (valid_input(input)) {
            input->valid = 1;
            break;
        // else clear input and repeat
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
    
    char *all_actions = "a,g,s,d,l,c,i,q,action,get,set,delete,list,clear,info,quit";
    if (strstr(all_actions, input->params[0]) == NULL) {
        printf("Such action does not exist\n");
        return 0;
    }


    char action = input->params[0][0];

    char *actions = "agsdlciq";
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

        char *one_args = "alicq";
        if (strchr(one_args, action) != NULL) {
            printf("Too much arguments for this action\n");
            return 0;
        }

        int id = atoi(input->params[1]);

        // id being equal to 0 in condition
        // below also validates from char input
        if (id <= 0 || id > MAX_ID) {
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


void get_car(Car *car) {
    car->make = malloc(MAX_TEXT_LENGTH);
    car->model= malloc(MAX_TEXT_LENGTH);
    
    int temp;
    int error;

    // Enter make
    while (1) {
        printf("Enter make > ");
        memset(car->make,0,sizeof(car->make));

        if (scanf("%[^\n]%*c", car->make) == 1) {

            error = 0;

            for (int i = 0; i < MAX_TEXT_LENGTH; i++) {
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

    // Enter model
    car->model = get_word("Enter model > ", car->model);

    // Enter year
    car->year =  get_num_interval("Enter year > ", "Please make sure that year is in normal format", EARLIEST_YEAR, LATEST_YEAR);

    // Enter price
    car->price = get_pos_num("Enter price > ", 0);

}




Connection *database_open(const char* filename) {
	Connection *conn = malloc(sizeof(Connection));
	if(!conn) die("Memory error");

    conn->db = malloc(sizeof(StaticDatabase));
    /*conn->db->capacity = 10;*/
    /*conn->db->size = 0;*/
    /*conn->db->rows = malloc(10 * sizeof(Address*));*/

	if(!conn->db) die("Memory error");

	conn->file = fopen(filename, "r+");

	if(conn->file) {
		// load database from file
		int rc = fread(conn->db, sizeof(StaticDatabase), 1, conn->file);

		// if database is loaded unsuccessfully
		if (rc != 1) {
			printf("Failed to load database\n");
			if (choice("Would you like to create a new one?\n")) {
				conn->file = fopen(filename, "w");
                database_create(conn);
                database_write(conn);
			}
		}
	}

	if (!conn->file) die("Failed to open the file");

	return conn;
}

void database_create(Connection *conn) {

    for (int i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize it
        Address addr = {.id = i, .set = 0};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

void database_write(Connection *conn) {
	rewind(conn->file);

	int rc = fwrite(conn->db, sizeof(StaticDatabase), 1, conn->file);
	if (rc != 1) die("Failed to write database");

	rc = fflush(conn->file);
	if (rc == -1) die("Cannot flush database");
}

void database_set(StaticDatabase* db, int id, Car *car) { 
    /*Address *addr = &(db->rows[db->size++]);*/
	Address *addr = &db->rows[id];

	debug("insdie");
	/*addr->car = malloc(sizeof(Car));*/

    /*addr->car = car;*/

    strcpy(addr->car_make, car->make);
    strcpy(addr->car_model, car->model);
    addr->car_year = car->year;
    addr->car_price = car->price;
    addr->set = 1;

    printf("Successfully saved, ID = %d\n", id);
}


void database_get(Connection *conn, int id) {
    Address *addr = &conn->db->rows[id];
    if (addr->set) {
        printf("__________________________________________________________________________________________\n");
        printf("| ID |            Make              |            Model             |   Year   |   Price  |\n");
        printf("|_ __|______________________________|______________________________|__________|__________|\n");
        address_print(addr);
    } else {
        printf("ID is not set\n");
    }
}


void database_list(StaticDatabase* db, int reverse) {
    int i = 0;
    int count = 0;

    printf("__________________________________________________________________________________________\n");
    printf("| ID |            Make              |            Model             |   Year   |   Price  |\n");
    printf("|_ __|______________________________|______________________________|__________|__________|\n");

    debug("HER");

    /*Database *db = conn->db;*/

    if (!reverse) {
        /*debug("reverse");*/
        /*debug("d size %d", db->size);*/
        /*for (i = 0; i < db->size; i++) {*/
        for (i = 0; i < MAX_ROWS; i++) {
            /*debug("iter %d", i);*/
            Address *cur = &db->rows[i];
            // FIXME nereikia ar is_set tikrinti
            if (cur->set) {
                count += 1;
                address_print(cur);
            }
        }
    } else {
        for (i = MAX_ROWS - 1; i >= 0; i--) {
            Address *cur = &db->rows[i];
            if (cur->set) {
                count += 1;
                address_print(cur);
            }
        }
    }
    debug("HER NOW");

    if (count == 0) {
        printf("No entries.\n");
    }
}

void address_print(Address *addr) {

    printf("|%4d|%30s|%30s|%10d|%10d|\n", addr->id, addr->car_make, addr->car_model, addr->car_year, addr->car_price);
    printf("|____|______________________________|______________________________|__________|__________|\n");
}


void database_delete(Connection *conn, int id) {
    if (conn->db->rows[id].set == 0) {
        printf("No such entry in database\n");
    } else {
        if (choice("Do you really want to delete this entry?")) {
            Address *cur = &conn->db->rows[id];
            /*free(cur->car);*/

            cur->set = 0;
            printf("Successfully deleted\n");
        }
    }
}


void database_clear(Connection *conn) {
    int i = 0;
    int count = 0;

    if (choice("Do you really want to clear the entire database?")) {

        for (i = 0; i < MAX_ROWS; i++) {
            Address *cur = &conn->db->rows[i];
            if (cur->set) {
                /*free(cur->car);*/
                cur->set = 0;
                count += 1;
            }
        }
        database_write(conn);

        if (count) {
            printf("Database has been successfully cleared.\n");
        } else {
            printf("Database has no entries. Nothing to clear.\n");
        }
    }
}

void database_close(Connection *conn) {
	if (conn) {
		if (conn->file) fclose(conn->file);
		if (conn->db) free(conn->db);
		free(conn);
	}
}


