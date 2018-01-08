#include <stdio.h>
#include <stdlib.h>

#include "f.h"

#ifndef HELLO
#define HELLO "Hello World"
#endif

int main(int argc, char *argv[]) {
    print(HELLO);
}

