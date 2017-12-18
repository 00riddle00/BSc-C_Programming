#ifndef TOP_DOWN_MERGE_SORT
#define TOP_DOWN_MERGE_SORT

#include <stdio.h>
#include <stdlib.h>


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

#endif
