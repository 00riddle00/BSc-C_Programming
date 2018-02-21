#ifndef __BINARY_FILE_
#define __BINARY_FILE_

#include <stdio.h>
#include <stdlib.h>
#include "database.h"

#define CHUNK_SIZE 2

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

// description
void database_create(Connection *conn);

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
