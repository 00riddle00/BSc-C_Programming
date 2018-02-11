#ifndef __FILTER_H_
#define __FILTER_H_

#include <stdio.h>
#include <string.h>

/*#define MAX_ROWS 100*/

//// database address ('set' - whether is set (exists) or not)
//typedef struct {
    //int id;
    //int set;
    //char car_make[10];
    //char car_model[10];
    //int car_year;
    //int car_price;
    //[>Car *car;<]
//} Address;

//// database
//typedef struct {
    //Address rows[MAX_ROWS];
/*} Database;*/

// functions to filter database in a given manner

// filter by car make
void filter_by_make(Database* db, int type, char* value);

// filter by car model
void filter_by_model(Database* db, int type, char* value);

// filter by car year
void filter_by_year(Database* db, int type, char* value);

// filter by car price
void filter_by_price(Database* db, int type, char* value);

#endif
