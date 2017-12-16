#include <stdio.h>
#include <stdlib.h>

#include "f.h"

#ifndef HELLO
#define HELLO "Hello World"

#endif /* HELLO */


int main(int argc, char *argv[]) {
    print(HELLO);

    printf("add(2,3):  %d\n", add(2, 3));
    printf("sub(2,3):  %d\n", sub(2, 3));

    printf("add(5,1):  %d\n", add(5, 1));
    printf("sub(7,2):   %d\n", sub(7, 2));

    printf("get add count:  %d\n", getAddCount());
    printf("get sub count:  %d\n", getSubCount());
    printf("get total count:   %d\n", getTotalCount());


    printf("exec(&add, 4, 5): %d\n", exec(&add, 4, 5));
    printf("exec(&sub, 6, 2):  %d\n", exec(&sub, 6, 2));

    return 0;
}
