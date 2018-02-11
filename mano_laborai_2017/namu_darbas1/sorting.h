#ifndef __SORTING_H_
#define __SORTING_H_

#include <stdio.h>

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

// functions to sort database in a given manner

// sort lexicographically by car make
Database* sort_lex_by_make(Database* db, int first, int last);

// sort lexicographically by car model
Database* sort_lex_by_model(Database* db, int first, int last);

// sort numerically by car year
Database* sort_by_year(Database* db, int first, int last);

// sort numerically by car price
Database* sort_by_price(Database* db, int first, int last);

#endif
