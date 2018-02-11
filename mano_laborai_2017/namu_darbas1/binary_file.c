#include <stdio.h>
#include <stdlib.h>

Connection *database_open(const char* filename) {
    Connection *conn = malloc(sizeof(Connection));
    if(!conn) die("Memory error");

    conn->db = malloc(sizeof(Database));
    if(!conn->db) die("Memory error");

    conn->file = fopen(filename, "r+");

    if(conn->file) {
        // load databae from file
        int rc = fread(conn->db, sizeof(Database), 1, conn->file);

        // if database is loaded unsucessfully
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


void database_write(Connection *conn) {
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(Database), 1, conn->file);
    if (rc != 1) die("Failed to write database");

    rc = fflush(conn->file);
    if (rc == -1) die("Cannot flush database");
}


void database_close(Connection *conn) {
    if (conn) {
        if (conn->file) fclose(conn->file);
        if (conn->db) free(conn->db);
        free(conn);
    }
}


