#ifndef __FILTER_H_
#define __FILTER_H_

#include <stdio.h>
#include <string.h>
#include "database.h"

// functions to filter database in a given manner

// reset filter
void reset_filter(Database* db);

// filter by car make
void filter_by_make(Database* db, int type, char* value);

// filter by car model
void filter_by_model(Database* db, int type, char* value);

// filter by car year
void filter_by_year(Database* db, int type, char* value);

// filter by car price
void filter_by_price(Database* db, int type, char* value);

#endif
