#include <stdio.h>
#include <stdlib.h>

#include "f.h"

static int addCount;
static int subCount;
static int totalCount;

void print(const char *message) {
    printf("%s\n", message);
}

int add(int x, int y) {
    addCount++;

    return x + y;
}

int sub(int x, int y) {
    subCount++;

    return x - y;
}

int getAddCount() {
    return addCount;
}


int getSubCount() {
    return subCount;
}

int getTotalCount() {
    return addCount+subCount;
}

int exec(int (*a)(), int x, int y) {
    return a(x, y);
}
