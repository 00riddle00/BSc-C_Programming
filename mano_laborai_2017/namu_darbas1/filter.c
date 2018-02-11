#include <stdio.h>
#include <string.h>

void filter_by_make(Database* db, int type, char* value) {

    switch(type) {
        case 1:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    if (strcmp(cur->car_make, value) != 0) {
                        cur->set = 0;
                    } 
                }
            }
            break;
        case 2:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    if (strstr(cur->car_make, value) == NULL) {
                        cur->set = 0;
                    } 
                }
            }
            break;
        case 3:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    if (strcmp(cur->car_make, value) == 0) {
                        cur->set = 0;
                    } 
                }
            }
            break;
        case 4:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    if (strstr(cur->car_make, value) != NULL) {
                        cur->set = 0;
                    } 
                }
            }
            break;
    }
}

void filter_by_model(Database* db, int type, char* value) {

    switch(type) {
        case 1:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    if (strcmp(cur->car_model, value) != 0) {
                        cur->set = 0;
                    } 
                }
            }
            break;
        case 2:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    if (strstr(cur->car_model, value) == NULL) {
                        cur->set = 0;
                    } 
                }
            }
            break;
        case 3:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    if (strcmp(cur->car_model, value) == 0) {
                        cur->set = 0;
                    } 
                }
            }
            break;
        case 4:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    if (strstr(cur->car_model, value) != NULL) {
                        cur->set = 0;
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
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    sprintf(year_string, "%d", cur->car_year);
                    if (strcmp(year_string, value) != 0) {
                        cur->set = 0;
                    } 
                }
            }
            break;
        case 2:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    sprintf(year_string, "%d", cur->car_year);
                    if (strstr(year_string, value) == NULL) {
                        cur->set = 0;
                    } 
                }
            }
            break;
        case 3:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    sprintf(year_string, "%d", cur->car_year);
                    if (strcmp(year_string, value) == 0) {
                        cur->set = 0;
                    } 
                }
            }
            break;
        case 4:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    sprintf(year_string, "%d", cur->car_year);
                    if (strstr(year_string, value) != NULL) {
                        cur->set = 0;
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
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    sprintf(price_string, "%d", cur->car_price);
                    if (strcmp(price_string, value) != 0) {
                        cur->set = 0;
                    } 
                }
            }
            break;
        case 2:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    sprintf(price_string, "%d", cur->car_price);
                    if (strstr(price_string, value) == NULL) {
                        cur->set = 0;
                    } 
                }
            }
            break;
        case 3:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    sprintf(price_string, "%d", cur->car_price);
                    if (strcmp(price_string, value) == 0) {
                        cur->set = 0;
                    } 
                }
            }
            break;
        case 4:
            for (int i = 0; i < MAX_ROWS; i++) {
                Address *cur = &db->rows[i];
                if (cur->set) {
                    sprintf(price_string, "%d", cur->car_price);
                    if (strstr(price_string, value) != NULL) {
                        cur->set = 0;
                    } 
                }
            }
            break;
    }
}



