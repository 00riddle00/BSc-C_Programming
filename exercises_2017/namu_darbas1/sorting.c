#include <stdio.h>

#include "sorting.h"
#include "database.h"

void sort_lex_by_make(Database* db, int first, int last) {

    int i, j;
    Address* temp;

    for (i = first; i < last; ++i)

        for (j = i + 1; j < last + 1; ++j) {

            if (strcmp(db->rows[i]->car_make, db->rows[j]->car_make) > 0) {
                temp = db->rows[i];
                db->rows[i] = db->rows[j];
                db->rows[j] = temp;
            }
        }
}


void sort_lex_by_model(Database* db, int first, int last) {

    int i, j;
    Address* temp;

    for (i = first; i < last; ++i)

        for (j = i + 1; j < last + 1; ++j) {

            if (strcmp(db->rows[i]->car_model, db->rows[j]->car_model) > 0) {
                temp = db->rows[i];
                db->rows[i] = db->rows[j];
                db->rows[j] = temp;
            }
        }
}

void sort_by_year(Database* db, int first, int last) {

    Address* temp;
    int pivot, j, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (
                db->rows[i]->car_year <= db->rows[pivot]->car_year && i < last) {
                i++;
            }
            while (db->rows[j]->car_year > db->rows[pivot]->car_year) {
                j--;
            }
            if (i < j) {
                temp = db->rows[i];
                db->rows[i] = db->rows[j];
                db->rows[j] = temp;
            }
        }

        temp = db->rows[pivot];
        db->rows[pivot] = db->rows[j];
        db->rows[j] = temp;

        sort_by_year(db, first, j - 1);
        sort_by_year(db, j + 1, last);
    }
}

void sort_by_price(Database* db, int first, int last) {

    Address* temp;
    int pivot, j, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (
                db->rows[i]->car_price <= db->rows[pivot]->car_price && i < last) {
                i++;
            }
            while (db->rows[j]->car_price > db->rows[pivot]->car_price) {
                j--;
            }
            if (i < j) {
                temp = db->rows[i];
                db->rows[i] = db->rows[j];
                db->rows[j] = temp;
            }
        }

        temp = db->rows[pivot];
        db->rows[pivot] = db->rows[j];
        db->rows[j] = temp;

        sort_by_price(db, first, j - 1);
        sort_by_price(db, j + 1, last);
    }
}


void sort_by_id(Database* db, int first, int last)
{

    Address* temp;
    int pivot, j, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (
                db->rows[i]->id <= db->rows[pivot]->id && i < last) {
                i++;
            }
            while (db->rows[j]->id > db->rows[pivot]->id) {
                j--;
            }
            if (i < j) {
                temp = db->rows[i];
                db->rows[i] = db->rows[j];
                db->rows[j] = temp;
            }
        }

        temp = db->rows[pivot];
        db->rows[pivot] = db->rows[j];
        db->rows[j] = temp;

        sort_by_id(db, first, j - 1);
        sort_by_id(db, j + 1, last);
    }
}

