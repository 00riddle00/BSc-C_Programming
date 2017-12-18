#ifndef BUBBLE_SORT_B_AND_E
#define BUBBLE_SORT_B_AND_E

#include <stdio.h>
#include <stdlib.h>

/* mišrus burbuliuko rikiavimo metodas, sujungiant a)-f) savybes vienokia ar kitokia tvarka */

 /* b)  lyginimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 remiasi faktu, kad į - asis masyvo perbėgimas į - ąjį pagal dydį elementą
 „nutempia“ į galutinę jo poziciją, ir naujo perbėgimo metu savo vietoje
 esančio elemento nebetikrina */

 /* e)  priskyrimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 gali keisti vietomis daugiau negu du elementus, t.y. vieną iš keistinų
 elementų jis pastumia iškart, o kitą įrašo į masyvą tiktai tuo atveju,
 jei jo tuojau pat nebereikės st umti iš tos pozicijos vėl */
int* bubble_sort_b_and_e(int* target, int size);

#endif
