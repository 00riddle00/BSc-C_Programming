#include <stdio.h>
#include <string.h>
#include "database.h"

void reset_filter(Database* db) {

    for (int i = 0; i < db->size; i++) {
        Address *cur = db->rows[i];
        if (cur) {
            cur->filter = 1;
        }
    }
}

void filter_by_make(Database* db, int type, char* value) {

    switch(type) {
        case 1:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    if (strcmp(cur->car_make, value) != 0) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
        case 2:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    if (strstr(cur->car_make, value) == NULL) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
        case 3:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    if (strcmp(cur->car_make, value) == 0) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
        case 4:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    if (strstr(cur->car_make, value) != NULL) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
    }
}

void filter_by_model(Database* db, int type, char* value) {

    switch(type) {
        case 1:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    if (strcmp(cur->car_model, value) != 0) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
        case 2:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    if (strstr(cur->car_model, value) == NULL) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
        case 3:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    if (strcmp(cur->car_model, value) == 0) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
        case 4:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    if (strstr(cur->car_model, value) != NULL) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
    }
}


void filter_by_year(Database* db, int type, char* value) {

    char year_string[MAX_TEXT_LENGTH];

    switch(type) {
        case 1:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    sprintf(year_string, "%d", cur->car_year);
                    if (strcmp(year_string, value) != 0) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
        case 2:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    sprintf(year_string, "%d", cur->car_year);
                    if (strstr(year_string, value) == NULL) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
        case 3:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    sprintf(year_string, "%d", cur->car_year);
                    if (strcmp(year_string, value) == 0) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
        case 4:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    sprintf(year_string, "%d", cur->car_year);
                    if (strstr(year_string, value) != NULL) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
    }
}


void filter_by_price(Database* db, int type, char* value) {

    char price_string[MAX_TEXT_LENGTH];

    switch(type) {
        case 1:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    sprintf(price_string, "%d", cur->car_price);
                    if (strcmp(price_string, value) != 0) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
        case 2:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    sprintf(price_string, "%d", cur->car_price);
                    if (strstr(price_string, value) == NULL) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
        case 3:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    sprintf(price_string, "%d", cur->car_price);
                    if (strcmp(price_string, value) == 0) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
        case 4:
            for (int i = 0; i < db->size; i++) {
                Address *cur = db->rows[i];
                if (cur) {
                    sprintf(price_string, "%d", cur->car_price);
                    if (strstr(price_string, value) != NULL) {
                        cur->filter = 0;
                    } 
                }
            }
            break;
    }
}



