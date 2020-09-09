/* Compiler: gcc */
/* CFLAGS=-Wall -xc -g */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_SIZE 100


void get(int **a, int **b);
void sort(int *a, int l);
void number(int **b);
void die(const char *message);


int main() {
    int *a = NULL;
    int *b = NULL;

    get(&a, &b);
    if (a == NULL) die("Memory error");

    sort(a, *b);

    printf("Sorted array of random numbers, marking even (0) and odd (1) numbers:\n");
    for (int i = 0; i < *b;
         printf("%d ", a[i++])) { }
    printf("\n");

    free(a);
    free(b);
}


void sort(int *a, int l) {

    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < l - 1; j++) {
            if (a[1 + j] <= a[j]) {
                char temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}


void number(int **b) {
    printf("Enter the size of an array\n");
    while (1) {
        printf("> ");
        if ((scanf("%d", *b) == 1) && (**b <= MAX_SIZE) && (**b > 0) && (getchar() == '\n')) {
            break;
        } else {
            printf("Size should be a positive integer, not exceeding the maximum size (100)\n");
            while (getchar() != '\n');
        }
    }
}


void get(int **a, int **b) {
    *b = malloc(sizeof(int));
    if (b == NULL) die("Memory error");
    number(b);
    int i;

    *a = (int *) malloc(**b * sizeof(int));
    if (*a == NULL) die("Memory error");
    for (i = 0; i < **b;) {
        (*a)[i++] = rand() % 2;
    }
}


void die(const char *message) {
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}
