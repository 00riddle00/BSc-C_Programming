// This module provides functions, which is necessary working with stack.

// Version history:
// v0: Created mod.c and mod.h files
// v1: used if sentences to fix some problems
//     added debugging mode (#define DEBUG 0)
// v2: now functions can operate with all types of variables

#define DEBUG 0
#include<stdio.h>
#include"mod.h"

//------------------------------------------------------------------------------
void push(struct Stack *s, void* value, int valueSize)
{
  if (s->size >= MAX_DATA - 1)
  {
    #if DEBUG
      printf("Elementas nepridetas. Neuztenka masyve vietos.\n");
    #endif
  }
  else
  {
    s->data[s->size] = malloc(valueSize);
  memcpy(s->data[s->size++], value, valueSize);
    #if DEBUG
      printf("Pridetas elementas.\n");
    #endif
  }
}

//------------------------------------------------------------------------------
void* pop(struct Stack *s)
{
  if (s->size > 0)
  {
    #if DEBUG
      printf("ispopintas elementas.\n");
    #endif
    return s->data[--s->size];
  }
}

