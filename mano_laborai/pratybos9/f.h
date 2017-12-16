#ifndef F_H
#define F_H


#include <stdio.h>
#include <stdlib.h>

#define HELLO "Hello Universe"


void print(const char *message);

int add(int x, int y);

int sub(int x, int y);


int getAddCount();

int getSubCount();

int getTotalCount();

int exec(int (*a)(), int x, int y);

#endif

