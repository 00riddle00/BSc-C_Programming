/* Compiler: gcc */
/* CFLAGS=-Wall -xc -g */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void getsize(int *size);
void getmemory(int **data, int size);
void filldata(int *data, int size);
void print(int *data, int size);
void die();


int main(int argc, char *argv[]) {
    int size;
    printf("Įveskite masyvo dydį\n> ");
    getsize(&size);

    int *data = NULL;
    getmemory(&data, size);
    if (data == NULL) die("Atminties problema");

    filldata(data, size);
    if (data == NULL) die("Atminties problema");

    print(data, size);
    free(data);
}


void getsize(int *size) {
    scanf("%d", size);
}


void getmemory(int **data, int size) {
    *data = malloc(size * sizeof(int));
}


void filldata(int *data, int size) {
    srand(time(NULL));
    int i;

    for (i = 0; i < size; i++) {
        data[i] = rand();
    }
}


void print(int *data, int size) {
    int i;
    printf("Jūsų sugeneruoti skaičiai:\n");
    for (i = 0; i < size; i++) {
        printf("%d\n", data[i]);
    }
}

void die(char *message) {
    printf("%s\n", message);
    exit(1);
}
