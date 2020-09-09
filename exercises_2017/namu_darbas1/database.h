#ifndef __DATABASE_H_
#define __DATABASE_H_

#include <stdio.h>
#include <string.h>

#define MAX_TEXT_LENGTH 30

// database address 
typedef struct {
    int id;
    int filter;
    char car_make[MAX_TEXT_LENGTH];
    char car_model[MAX_TEXT_LENGTH];
    int car_year;
    int car_price;
} Address;

// database
typedef struct {
    Address** rows;
    int size;
    int capacity;
} Database;

#endif
