#ifndef __SORTING_H_
#define __SORTING_H_

#include <stdio.h>
#include "database.h"

// functions to sort database in a given manner

// sort numerically by entry id
void sort_by_id(Database* db, int first, int last);

// sort lexicographically by car make
void sort_lex_by_make(Database* db, int first, int last);

// sort lexicographically by car model
void sort_lex_by_model(Database* db, int first, int last);

// sort numerically by car year
void sort_by_year(Database* db, int first, int last);

// sort numerically by car price
void sort_by_price(Database* db, int first, int last);

#endif




