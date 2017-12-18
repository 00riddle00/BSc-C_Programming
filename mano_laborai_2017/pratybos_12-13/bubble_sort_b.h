#ifndef BUBBLE_SORT_B
#define BUBBLE_SORT_B

#include <stdio.h>
#include <stdlib.h>
/* b)  lyginimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 remiasi faktu, kad į - asis masyvo perbėgimas į - ąjį pagal dydį elementą
 „nutempia“ į galutinę jo poziciją, ir naujo perbėgimo metu savo vietoje
 esančio elemento nebetikrina */
int* bubble_sort_b(int* data, int size);

#endif
