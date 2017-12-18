#ifndef BUBBLE_SORT_C_AND_F
#define BUBBLE_SORT_C_AND_F

#include <stdio.h>
#include <stdlib.h>

/* mišrus burbuliuko rikiavimo metodas, sujungiant a)-f) savybes vienokia ar kitokia tvarka */

 /* c)  lyginimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 papildomai stebi, ar duomenys tapo išrikiuoti, sekdamas ar perbėgimo
 metu buvo atliktas nors vienas sukeitimas, ir jei ne – vadinasi tęsti
 nebereikia */

 /* f)  „dvipusio“ rikiavimo algoritmas, kuris vieno perbėgimo metu didina
 lyginamų elementų indeksus, o kito perbėgimo metu juos mažina
 (žr. bidirectional bubble sort) */


int* bubble_sort_c_and_f(int* target, int size);

#endif
