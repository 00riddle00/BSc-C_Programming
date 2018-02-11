#ifndef __BINARY_FILE_
#define __BINARY_FILE_

#include <stdio.h>
#include <stdlib.h>

//// database address ('set' - whether is set (exists) or not)
//typedef struct {
    //int id;
    //int set;
    //char car_make[10];
    //char car_model[10];
    //int car_year;
    //int car_price;
//} Address;

//// database
//typedef struct {
    //Address rows[MAX_ROWS];
//} Database;

// has a pointer to file and a pointer to database
typedef struct {
    FILE *file;
    Database *db;
} Connection;


// open database from file. If file does not
// exist, return an error and exit. If database is failed
// to load, prompt user to create a new database
//
// ::params: filename - name of a file
// ::return: connection struct
Connection *database_open(const char* filename);


// write current state of database to a file
//
// ::params: conn - Connection struct
void database_write(Connection *conn);

// close connection to a file, and free
// database (conn->db) as well as connection (conn) structs
// 
// ::params: conn - Connection struct
void database_close(Connection *conn);

#endif
