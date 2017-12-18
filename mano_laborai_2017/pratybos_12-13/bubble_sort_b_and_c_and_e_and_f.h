#ifndef BUBBLE_SORT_B_AND_C_AND_E_AND_F
#define BUBBLE_SORT_B_AND_C_AND_E_AND_F

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

 /* e)  priskyrimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 gali keisti vietomis daugiau negu du elementus, t.y. vieną iš keistinų
 elementų jis pastumia iškart, o kitą įrašo į masyvą tiktai tuo atveju,
 jei jo tuojau pat nebereikės st umti iš tos pozicijos vėl */

 /* f)  „dvipusio“ rikiavimo algoritmas, kuris vieno perbėgimo metu didina
 lyginamų elementų indeksus, o kito perbėgimo metu juos mažina
 (žr. bidirectional bubble sort) */


int* bubble_sort_b_and_c_and_e_and_f(int* target, int size);

#endif
