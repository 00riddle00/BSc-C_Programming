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
 | 			      screen. Each time the program runs, the log entry is created in 
 |                ./log.txt file, with the info about the beginning of the program 
 |                 and how much time did it run.
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
 |       TODOS:   (1) Add unit tests
 |
 | Version
 | updates:       Version 1.5
 |
 +===========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#include "dbg.h"
#include "database.h"
#include "binary_file.h"
#include "filter.h"
#include "sorting.h"
#include "lib_riddle.h"

#define MAX_LINE 100
#define MAX_TEXT_LENGTH 30
#define MAX_PARAMS 2
#define LATEST_YEAR 2018
#define EARLIEST_YEAR 1920
#define CHUNK_SIZE 2
#define LOGFILE "log.txt"

// car (make, model, year of making, car price)
typedef struct {
    char *make;
    char *model;
    int year;
    int price;
} Car;

// input structure
typedef struct {
    int count;
    int valid;
    char** params;
} Input;

// function for debugging
// print the table including empty spaces
//
// ::params: conn - Connection structure
void debugTable(Connection* conn);

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

// print the heading of the table
void print_heading();

// print address from database
//
// ::params: addr - Address
void address_print(Address *addr);

// perform action on a database
// (filtering or sorting)
//
// ::params: action - Number, indicating the type of action
// ::params: db - Database
void perform_action(int action, Database* db);

// this function gets called with atexit()
// writes logging info to a log file and 
// displays goodbye message
void exiting();

// set Address struct in database
//
// ::params: db - Database
// ::params: id - entry id (user input)
// ::params: car - car struct
void database_set(Connection* conn, int id, Car *car);

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
void database_list(Database* db, int reverse);

// get entries from database, if they pass the filter
// (check if address->filter is true)
//
// ::params: db - Database
// ::params: reverse - whether to print in 
// reverse order (used in sorting)
void database_list_filtered(Database* db, int reverse);

// delete address from database
//
// ::params: conn - Connection struct
// ::params: id - entry id (user input)
void database_delete(Connection* conn, int id);

// clear database
// 
// ::params: conn - Connection struct
void database_clear(Connection *conn);

clock_t begin;
clock_t end;

double clocks;
double time_spent;

static FILE* logfile;


int main(int argc, char *argv[]) {

    if (argc < 2) die ("USAGE: test <dbfile> <action> [action params]");

    logfile = fopen(LOGFILE, "ab+");

    time_t current_time;
    char* c_time_string;

    current_time = time(NULL);

    /* Convert to local time format. */
    c_time_string = ctime(&current_time);

    fprintf(logfile, "Starting program @%s", c_time_string);
    begin = clock();

    /* register the termination function */
    atexit(exiting);

    char* filename = argv[1];
    Connection* conn = database_open(filename);

    char* about = "This is a car database program, where one can perform get, list, create, edit and delete "
            "operations. The database is loaded from and saved to the binary file. Version: v.0";

    char* info = "Usage: in the main shell, input the Action[1] and ID[2].\n\n[1] Action - g=get, l=list, "
        "s=set, d=delete, c=clear database, q=quit, i=info.\n[2] ID - a positive integer. Only get, "
        "set and delete operations require ID parameter.\nExamples: (1) get 1 (get 1st element) (2) l (list elements) "
        "(3) set 2 (set 2nd element)";

    char* separator = "---------------------------------------------------";

    // shows whether the were command line arguments to a program
    int cmd = 0;

    // id for database entries
    int id;

    /* initialize input variable*/
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

                Database *db = conn->db;
                action = get_num_interval("(Enter a number) > ", "Such option does not exist", 1, 2);
                perform_action(action, db);
                break;
            case 'g':
                database_get(conn, id);
                break;
            case 's':; // An empty statement before a label
                int no_change = 0;

				for (int i = 0; i < conn->db->capacity; i++) {
                    if (conn->db->rows[i]->id == id) {
                        printf("Such entry already exists:\n");
                        database_get(conn, id);
                        if (choice("Would you like to change it?")) {
                            database_delete(conn, id);
                            database_write(conn);
                        } else {
                            no_change = 1;
                            break;
                        }
                    }
                }
                if (no_change)
                    break;

                Car *car = malloc(sizeof(Car));
                if (car == NULL) die("Memory error");
                get_car(car);

                if (choice("Would you like to save?")) {
                    database_set(conn, id, car);
					database_write(conn);
                }
                break;
            case 'd':
                database_delete(conn, id);
                database_write(conn);
                break;
            case 'l':
                sort_by_id(conn->db, 0, conn->db->size - 1);
				database_list(conn->db, 0);
                break;
            case 'c':
                database_clear(conn);
                break;
            case 'i':
                printf("\n%s\n", separator);
                printf("%s\n\n", info);
                debugTable(conn);
                break;
            case 'q':
                database_close(conn);
                return 0;
            default:
                printf("Invalid action, only: g=get, s=set, d=delete, l=list, q=quit, i=info\n");
        }

    }
}


// function for debugging
void debugTable(Connection* conn) {
    int i = 0;

    debug("db size: %d", conn->db->size);
    debug("db capacity: %d", conn->db->capacity);

    printf("__________________________________________________________________________________________\n");
    printf("| ID |            Make              |            Model             |   Year   |   Price  |\n");
    printf("|_ __|______________________________|______________________________|__________|__________|\n");

    for (i = 0; i < conn->db->capacity; i++) {
        address_print(conn->db->rows[i]);
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
        if (id <= 0) {
            printf("ID should be a positive integer.\n");
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

void print_heading() {
    printf("__________________________________________________________________________________________\n");
    printf("| ID |            Make              |            Model             |   Year   |   Price  |\n");
    printf("|_ __|______________________________|______________________________|__________|__________|\n");
}

void address_print(Address *addr) {

    printf("|%4d|%30s|%30s|%10d|%10d|\n", addr->id, addr->car_make, addr->car_model, addr->car_year, addr->car_price);
    printf("|____|______________________________|______________________________|__________|__________|\n");
}


void perform_action(int action, Database* db) {
    int field; 
    int type;
    char* value;

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

            switch(field) {
                case 1:
                    filter_by_make(db, type, value);
                    break;
                case 2:
                    filter_by_model(db, type, value);
                    break;
                case 3:
                    filter_by_year(db, type, value);
                    break;
                case 4:
                    filter_by_price(db, type, value);
                    break;
            }
            database_list_filtered(db, 0);
            reset_filter(db);
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

            switch(field) {
                case 1:
                    sort_lex_by_make(db, 0, db->size - 1);
                    break;
                case 2:
                    sort_lex_by_model(db, 0, db->size - 1);
                    break;
                case 3:
                    sort_by_year(db, 0, db->size - 1);
                    break;
                case 4:
                    sort_by_price(db, 0, db->size - 1);
                    break;
            }
            database_list(db, reverse);
            break;
    }

}

void exiting() {
    end = clock();

    clocks = (double)(end - begin);
    time_spent = clocks / CLOCKS_PER_SEC;
    fprintf(logfile, "Time spent: %lf seconds\n", time_spent);
    fputs("-----------------------\n", logfile);
    printf("Goodbye!\n");
}

void database_set(Connection* conn, int id, Car *car) { 
    if (conn->db->size == conn->db->capacity) {
        conn->db->capacity += CHUNK_SIZE;
        conn->db->rows = realloc(conn->db->rows, conn->db->capacity * sizeof(Address*));
        for (int i = conn->db->size; i < conn->db->capacity; i++) {
            conn->db->rows[i] = calloc(1, sizeof(Address));
        }
    }
   
    int i;
    for (i = 0; i < conn->db->capacity; i++) {
        if (conn->db->rows[i]->id == 0) {
            break;
        }
    }

    strcpy(conn->db->rows[i]->car_make, car->make);
    strcpy(conn->db->rows[i]->car_model, car->model);
    conn->db->rows[i]->car_year = car->year;
    conn->db->rows[i]->car_price = car->price;
    conn->db->rows[i]->id = id;
    conn->db->rows[i]->filter = 1;

    conn->db->size += 1;

    printf("Successfully saved, ID = %d\n", id);
}


void database_get(Connection *conn, int id) {
    for (int i = 0; i < conn->db->size; i++) {
        Address *addr = conn->db->rows[i];
        if (addr->id == id) {
            if (addr) {
                print_heading();
                address_print(addr);
                return;
            } 
        }
    }
    printf("ID is not set\n");
}


void database_list(Database* db, int reverse) {

    print_heading();

    if (db->size == 0) {
        printf("No entries.\n");
        return;
    }

    int i = 0;

    if (!reverse) {
        for (i = 0; i < db->capacity; i++) {
            if (db->rows[i]->id) {
                address_print(db->rows[i]);
            }
        }
    } else {
        for (i = db->capacity - 1; i >= 0; i--) {
            if (db->rows[i]->id) {
                address_print(db->rows[i]);
            }
        }
    }

}



void database_list_filtered(Database* db, int reverse) {

    print_heading();

    if (db->size == 0) {
        printf("No entries.\n");
        return;
    }

    int i = 0;

    if (!reverse) {
        for (i = 0; i < db->capacity; i++) {
            if (db->rows[i]->filter) {
                address_print(db->rows[i]);
            }
        }
    } else {
        for (i = db->capacity - 1; i >= 0; i--) {
            if (db->rows[i]->filter) {
                address_print(db->rows[i]);
            }
        }
    }

}

void database_delete(Connection *conn, int id) {
    for (int i = 0; i < conn->db->capacity; i++) {
        Address *addr = conn->db->rows[i];
        if (addr->id == id) {
            if (choice("Do you really want to delete this entry?")) {
                addr->id = 0;
                conn->db->rows[i] = calloc(1, sizeof(Address));
                conn->db->size--;
                printf("Successfully deleted\n");
                return;
            }
        }
    }
    printf("No such entry in database\n");
}


void database_clear(Connection *conn) {

    if (!conn->db->size) {
        printf("Database has no entries. Nothing to clear.\n");
        return;
    }

    if (choice("Do you really want to clear the entire database?")) {

        conn->db->size = 0;

        for (int i = 0; i < conn->db->capacity; i++) {
            free(conn->db->rows[i]);
        }
        database_create(conn);
        database_write(conn);
        printf("Database has been successfully cleared.\n");

    }
}

