#ifndef BUBBLE_SORT_B_AND_C
#define BUBBLE_SORT_B_AND_C

#include <stdio.h>
#include <stdlib.h>

/* mišrus burbuliuko rikiavimo metodas, sujungiant a)-f) savybes vienokia ar kitokia tvarka */

 /* b)  lyginimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 remiasi faktu, kad į - asis masyvo perbėgimas į - ąjį pagal dydį elementą
 „nutempia“ į galutinę jo poziciją, ir naujo perbėgimo metu savo vietoje
 esančio elemento nebetikrina */

 /* c)  lyginimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 papildomai stebi, ar duomenys tapo išrikiuoti, sekdamas ar perbėgimo
 metu buvo atliktas nors vienas sukeitimas, ir jei ne – vadinasi tęsti
 nebereikia */
int* bubble_sort_b_and_c(int* target, int size);

#endif
