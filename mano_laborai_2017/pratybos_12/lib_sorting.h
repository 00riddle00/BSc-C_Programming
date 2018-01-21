#ifndef _LIB_SORTING_
#define _LIB_SORTING_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// How many comparisons are made between neighbor element
extern int count_ncomp;

// Assignment operation count
extern int count_assign;

extern clock_t begin;
extern clock_t end;

extern double clocks;
extern double time_spent;

void swap(int* a, int* b);
void swap_three(int* a, int* b, int* c);

int* bubble_sort_a(int* data, int size);
int* bubble_sort_b(int* data, int size);
int* bubble_sort_c(int* target, int size);
int* bubble_sort_d(int* target, int size);
int* bubble_sort_e(int* target, int size);
int* bubble_sort_e_and_f(int* target, int size);
int* bubble_sort_f(int* target, int size);
int* bubble_sort_b_and_c(int* target, int size);
int* bubble_sort_b_and_e(int* target, int size);
int* bubble_sort_b_and_f(int* target, int size);
int* bubble_sort_c_and_e(int* target, int size);
int* bubble_sort_c_and_f(int* target, int size);
int* bubble_sort_b_and_e_and_f(int* target, int size);
int* bubble_sort_b_and_c_and_e_and_f(int* target, int size);
int* quicksort(int* target, int start, int end);
int* QuickSortMedian(int* a, int start, int end);
int* QuickSortRandomAndMedian(int* a, int start, int end);

int* insertion_sort(int* target, int size);
int* selection_sort(int* target, int size);

// Array A[] has the items to sort; array B[] is a work array.
void TopDownMergeSort(int* A, int* B, int n);

// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge(int* B, int iBegin, int iEnd, int* A);

//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge(int* A, int iBegin, int iMiddle, int iEnd, int* B);

void CopyArray(int* A, int iBegin, int iEnd, int* B);

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int* heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);
void buildHeap(int arr[], int n);
void printArray(int* arr, int n);

#endif
