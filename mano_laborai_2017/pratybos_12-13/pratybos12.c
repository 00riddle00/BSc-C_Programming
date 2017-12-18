/*=============================================================================
 |
 |  Assignment:  Program 12-13
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Programming Basics
 |         Date:  December 13th, 2017
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |   To Compile:  gcc -Wall -xc -g -std=c99 pratybos12.c -o pratybos12
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  Sorting algortihm testing program using pseudo randomly 
 |                generated number array. User can specify array length, 
 |                its min and max elements, the least number of repeating 
 |                values. User can also choose how many arrays to be tested.
 |
 |	    Input:    Command line input by user
 |
 |	    Output:   Prompt messages, validation errors and final results
 |                are displayed one per line to the standard output.
 |                The output is each algorithm's each iteration, with
 |                comparison and assignment counts, and also processor
 |                clock times and average completion time, in seconds.
 |                Finally, the average data of each algorithm is presented.
 |                At the end, the algorithms are sorted from best to worst
 |                by their average time.
 |
 | Version
 | updates:     Currently this is the intial version
 |
 +===========================================================================*/

/* Explanations
 *
 a)  naivus rikiavimo algoritmas, kuris perbėga visą n dydžio masyvą n kartų,
 lygindamas greta esan čius elementus tarpusavyje ir keisdamas juos
 vietomis, jei tvarka netinkama
 b)  lyginimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 remiasi faktu, kad į - asis masyvo perbėgimas į - ąjį pagal dydį elementą
 „nutempia“ į galutinę jo poziciją, ir naujo perbėgimo metu savo vietoje
 esančio elemento nebetikrina
 c)  lyginimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 papildomai stebi, ar duomenys tapo išrikiuoti, sekdamas ar perbėgimo
 metu buvo atliktas nors vienas sukeitimas, ir jei ne – vadinasi tęsti
 nebereikia
 d)  lyginimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 įsidėmi paskutinio sukeitimo vietą, ir remdamasis faktu, kad visi
 tolesni elementai jau yra savo vietoje, rikiuoja tik galimai nesurikiuotą
 masyvo dalį
 e)  priskyrimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 gali keisti vietomis daugiau negu du elementus, t.y. vieną iš keistinų
 elementų jis pastumia iškart, o kitą įrašo į masyvą tiktai tuo atveju,
 jei jo tuojau pat nebereikės st umti iš tos pozicijos vėl
 f)  „dvipusio“ rikiavimo algoritmas, kuris vieno perbėgimo metu didina
 lyginamų elementų indeksus, o kito perbėgimo metu juos mažina
 (žr. bidirectional bubble sort)
 x) toliau - mišrūs burbuliuko rikiavimo metodai, sujungiant a)-f) savybes
 vienokia ar kitokia tvarka
 g) greitojo rikiavimo metodas (angl. quicksort)
 h) Įterpimo metodas (angl. insertion sort)
 i) Išrinkimo metodas (angl. selection sort)
 j) Sąlajos metodas (angl. merge sort)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dbg.h"
#include "helpers.h"
#include "test_algorithm.h"

#include "bubble_sort_a.h"
#include "bubble_sort_b.h"
#include "bubble_sort_c.h"
#include "bubble_sort_d.h"
#include "bubble_sort_e.h"
#include "bubble_sort_f.h"
#include "bubble_sort_b_and_c.h"
#include "bubble_sort_b_and_e.h"
#include "bubble_sort_b_and_f.h"
#include "bubble_sort_c_and_e.h"
#include "bubble_sort_c_and_f.h"
#include "bubble_sort_e_and_f.h"
#include "bubble_sort_b_and_e_and_f.h"
#include "bubble_sort_b_and_c_and_e_and_f.h"
#include "quicksort.h"
#include "insertion_sort.h"
#include "selection_sort.h"
#include "top_down_merge_sort.h"

#define MAX_ITER 100
#define MAX_ALGO 100


typedef struct {
    char* pointerName;
    int pointerMemory;
} PointerStats;

typedef struct {
    PointerStats* memJournal;
    int JournalPointerCount;
    int memUsed;
    int memUsedByJournal;
} MemoryStats;


typedef struct {
    int no;
    int is_sorted;
    int comp_count;
    int assign_count;
    double clocks_total;
    double time_spent;
} Iteration;

typedef struct {
    char* type;
    char* complexity;
    int iter_count;
    int rank;
    int avg_comp;
    int avg_assign;
    double avg_clocks;
    double avg_time;
    Iteration* iterations[MAX_ITER];
} Algorithm;

typedef struct {
    char* date;
    char* arch;
    char* compiler;
    Algorithm* algorithms[MAX_ALGO];
} Results;

// a typedef creates a fake type, in this
// case for a sort function pointer
typedef int* (*sort_pointer)(int* target, int size);

// function pointer to a quicksort function
typedef int* (*quicksort_pointer)(int* target, int first, int last);

// function pointer to a mergesort function
typedef void (*mergesort_pointer)(int* target, int* working_array, int size);


void filldata(int* data, int size, int min, int max, int repeat);
void test_sort( int* data, int size, sort_pointer func, Algorithm* Algo, int no);
void test_quicksort( int* data, int size, quicksort_pointer func, Algorithm* Algo, int no);
void test_mergesort( int* data, int size, mergesort_pointer func, Algorithm* Algo, int no);
void print_algo(Algorithm* Algo);
void calculate_average(Algorithm* Algo);
Algorithm** rank_algorithms(Algorithm** target, int first, int last);

MemoryStats memoryStats;

int array_count;

int main(int argc, char* argv[])
{
    srand(time(NULL));

    Results* Res = malloc(sizeof(Results));

    Res->date = "2017-12-16";
    Res->arch = "Arch Linux x86_64";
    Res->compiler = "gcc";

    // creating algorithm structures
    Algorithm* Algo1 = malloc(sizeof(Algorithm));
    Algo1->type = "bubble_sort_a";
    Algo1->complexity = "O (n^2)";

    Algorithm* Algo2 = malloc(sizeof(Algorithm));
    Algo2->type = "bubble_sort_b";
    Algo2->complexity = "O (n^2)";

    Algorithm* Algo3 = malloc(sizeof(Algorithm));
    Algo3->type = "bubble_sort_c";
    Algo3->complexity = "O (n^2)";

    Algorithm* Algo4 = malloc(sizeof(Algorithm));
    Algo4->type = "bubble_sort_d";
    Algo4->complexity = "O (n^2)";

    Algorithm* Algo5 = malloc(sizeof(Algorithm));
    Algo5->type = "bubble_sort_e";
    Algo5->complexity = "O (n^2)";

    Algorithm* Algo6 = malloc(sizeof(Algorithm));
    Algo6->type = "bubble_sort_f";
    Algo6->complexity = "O (n^2)";

    Algorithm* Algo7 = malloc(sizeof(Algorithm));
    Algo7->type = "bubble_sort_b_and_c";
    Algo7->complexity = "O (n^2)";

    Algorithm* Algo8 = malloc(sizeof(Algorithm));
    Algo8->type = "bubble_sort_b_and_e";
    Algo8->complexity = "O (n^2)";

    Algorithm* Algo9 = malloc(sizeof(Algorithm));
    Algo9->type = "bubble_sort_b_and_f";
    Algo9->complexity = "O (n^2)";

    Algorithm* Algo10 = malloc(sizeof(Algorithm));
    Algo10->type = "bubble_sort_c_and_e";
    Algo10->complexity = "O (n^2)";

    Algorithm* Algo11 = malloc(sizeof(Algorithm));
    Algo11->type = "bubble_sort_c_and_f";
    Algo11->complexity = "O (n^2)";

    Algorithm* Algo12 = malloc(sizeof(Algorithm));
    Algo12->type = "bubble_sort_e_and_f";
    Algo12->complexity = "O (n^2)";

    Algorithm* Algo13 = malloc(sizeof(Algorithm));
    Algo13->type = "bubble_sort_b_and_e_and_f";
    Algo13->complexity = "O (n^2)";

    Algorithm* Algo14 = malloc(sizeof(Algorithm));
    Algo14->type = "bubble_sort_b_and_c_and_e_and_f";
    Algo14->complexity = "O (n^2)";

    Algorithm* Algo15 = malloc(sizeof(Algorithm));
    Algo15->type = "quicksort";
    Algo15->complexity = "O (n logn n)";

    Algorithm* Algo16 = malloc(sizeof(Algorithm));
    Algo16->type = "insertion_sort";
    Algo16->complexity = "O (2n)";

    Algorithm* Algo17 = malloc(sizeof(Algorithm));
    Algo17->type = "selection_sort";
    Algo17->complexity = "O (2n)";

    Algorithm* Algo18 = malloc(sizeof(Algorithm));
    Algo18->type = "top down merge sort";
    Algo18->complexity = "O (n log n)";

    Res->algorithms[0] = Algo1;
    Res->algorithms[1] = Algo2;
    Res->algorithms[2] = Algo3;
    Res->algorithms[3] = Algo4;
    Res->algorithms[4] = Algo5;
    Res->algorithms[5] = Algo6;
    Res->algorithms[6] = Algo7;
    Res->algorithms[7] = Algo8;
    Res->algorithms[8] = Algo9;
    Res->algorithms[9] = Algo10;
    Res->algorithms[10] = Algo11;
    Res->algorithms[11] = Algo12;
    Res->algorithms[12] = Algo13;
    Res->algorithms[13] = Algo14;
    Res->algorithms[14] = Algo15;
    Res->algorithms[15] = Algo16;
    Res->algorithms[16] = Algo17;
    Res->algorithms[17] = Algo18;

    memoryStats.memJournal = malloc(10 * sizeof(int));

    memoryStats.memUsedByJournal = 10;

    memoryStats.JournalPointerCount = 0;

    printf("Mem used total: %d\n", memoryStats.memUsed);

    int size;
    int min;
    int max;
    int repeat;

    array_count = get_pos_num("How many arrays would you like to test? > ", 0);
    size = get_pos_num("What is the size of each array? > ", 0);
    min = get_pos_num("What is the minimum number in each array? > ", 0);
    max = get_pos_num("What is the maximum number in each array? > ", 0);

    while (1) {
        printf("How many repeating values there will be AT LEAST? > ");
        if (scanf("%d", &repeat) == 1 && repeat >= 0
            && repeat <= (max - min + 1) && getchar() == '\n') {
            break;
        } else {
            while (getchar() != '\n')
                ;
            printf("Please enter a positive integer or zero, which is not "
                   "greater than the "
                   "size of the array\n");
        }
    }

    for (int i = 0; i < array_count; i++) {

        int* data = NULL;

        getmemory(&data, "data", size * sizeof(int));
        if (data == NULL)
            die("Atminties problema");

        filldata(data, size, min, max, repeat);
        if (data == NULL)
            die("Atminties problema");

        print_array(data, size, "Your generated numbers:");
        //---------------------------USING FUNCTION POINTERS-----------------//

        test_sort(data, size, &bubble_sort_a, Algo1, i + 1);
        test_sort(data, size, &bubble_sort_b, Algo2, i + 1);
        test_sort(data, size, &bubble_sort_c, Algo3, i + 1);
        test_sort(data, size, &bubble_sort_d, Algo4, i + 1);
        test_sort(data, size, &bubble_sort_e, Algo5, i + 1);
        test_sort(data, size, &bubble_sort_f, Algo6, i + 1);
        test_sort(data, size, &bubble_sort_b_and_c, Algo7, i + 1);
        test_sort(data, size, &bubble_sort_b_and_e, Algo8, i + 1);
        test_sort(data, size, &bubble_sort_b_and_f, Algo9, i + 1);
        test_sort(data, size, &bubble_sort_c_and_e, Algo10, i + 1);
        test_sort(data, size, &bubble_sort_c_and_f, Algo11, i + 1);
        test_sort(data, size, &bubble_sort_e_and_f, Algo12, i + 1);
        test_sort(data, size, &bubble_sort_b_and_e_and_f, Algo13, i + 1);
        test_sort(data, size, &bubble_sort_b_and_c_and_e_and_f, Algo14, i + 1);
        test_quicksort(data, size, &quicksort, Algo15, i + 1);
        test_sort(data, size, &insertion_sort, Algo16, i + 1);
        test_sort(data, size, &selection_sort, Algo17, i + 1);
        test_mergesort(data, size, &TopDownMergeSort, Algo18, i + 1);

        free(data);
    }

    calculate_average(Algo1);
    calculate_average(Algo2);
    calculate_average(Algo3);
    calculate_average(Algo4);
    calculate_average(Algo5);
    calculate_average(Algo6);
    calculate_average(Algo7);
    calculate_average(Algo8);
    calculate_average(Algo9);
    calculate_average(Algo10);
    calculate_average(Algo11);
    calculate_average(Algo12);
    calculate_average(Algo13);
    calculate_average(Algo14);
    calculate_average(Algo15);
    calculate_average(Algo16);
    calculate_average(Algo17);
    calculate_average(Algo18);


    for (int i = 0; i < 18; i++) {
        print_algo(Res->algorithms[i]);
    }


    Algorithm** target = malloc(18 * sizeof(Algorithm));

    target[0] = Algo1;
    target[1] = Algo2;
    target[2] = Algo3;
    target[3] = Algo4;
    target[4] = Algo5;
    target[5] = Algo6;
    target[6] = Algo7;
    target[7] = Algo8;
    target[8] = Algo9;
    target[9] = Algo10;
    target[10] = Algo11;
    target[11] = Algo12;
    target[12] = Algo13;
    target[13] = Algo14;
    target[14] = Algo15;
    target[15] = Algo16;
    target[16] = Algo17;
    target[17] = Algo18;

    target = rank_algorithms(target, 0, 17);

    printf("Fastest algorithms (ranking):\n");
    printf("=============================\n");

    for (int i = 0; i < 18; i++) {
        printf("%d. ", i + 1);
        printf("%s\n", target[i]->type);
        printf("Average time: %f\n", target[i]->avg_time);
        printf("---------------------------------\n");
    }

    printf("================================\n");
    printf("Date: %s\n", Res->date);
    printf("Architecture: %s\n", Res->arch);
    printf("Compiler: %s\n", Res->compiler);
    printf("================================\n");

    printf("Mem used total: %d\n", memoryStats.memUsed);
    free(memoryStats.memJournal);
}


void filldata(int* data, int size, int min, int max, int repeat)
{
    int i;

    for (i = 0; i < size; i++) {
        data[i] = min + rand() % (max - min + 1);
    }

    if (repeat > 1) {
        int repeat_value = min + rand() % (max - min + 1);

        int indexes[repeat];

        int x;

        // Non-duplicate number generation
        debug("%d", repeat);

        i = 0;
        while (i < repeat) {
            int index = rand() % size;
            debug("%d", index);

            for (x = 0; x < i; x++) {
                if (indexes[x] == index) {
                    break;
                }
            }
            if (x == i) {
                indexes[i++] = index;
            }
        }

        for (i = 0; i < repeat; i++) {
            debug("%d", indexes[i]);
            data[indexes[i]] = repeat_value;
        }
    }
}


void test_sort(int* data, int size, sort_pointer func, Algorithm* Algo, int no)
{

    count_ncomp = 0;
    count_assign = 0;

    begin = clock();

    int* target = malloc(size * sizeof(int));
    if (!target)
        die("Memory error.");

    memcpy(target, data, size * sizeof(int));

    Iteration* Iter = malloc(sizeof(Iteration));
    Iter->no = no;

    if (is_sorted(func(target, size), size)) {
        end = clock();
        clocks = (double)(end - begin);
        time_spent = clocks / CLOCKS_PER_SEC;

        Iter->is_sorted = 1;
        Iter->comp_count = count_ncomp;
        Iter->assign_count = count_assign;
        Iter->clocks_total = clocks;
        Iter->time_spent = time_spent;
    } else {
        Iter->is_sorted = 0;
    };

    Algo->iterations[no - 1] = Iter;

    free(target);
}

void test_quicksort(
    int* data, int size, quicksort_pointer func, Algorithm* Algo, int no)
{

    count_ncomp = 0;
    count_assign = 0;

    begin = clock();

    int* target = malloc(size * sizeof(int));
    if (!target)
        die("Memory error.");

    memcpy(target, data, size * sizeof(int));

    Iteration* Iter = malloc(sizeof(Iteration));
    Iter->no = no;

    if (is_sorted(func(target, 0, size - 1), size)) {
        end = clock();
        clocks = (double)(end - begin);
        time_spent = clocks / CLOCKS_PER_SEC;

        Iter->is_sorted = 1;
        Iter->comp_count = count_ncomp;
        Iter->assign_count = count_assign;
        Iter->clocks_total = clocks;
        Iter->time_spent = time_spent;
    } else {
        Iter->is_sorted = 0;
    };

    Algo->iterations[no - 1] = Iter;

    free(target);
}

void test_mergesort(
    int* data, int size, mergesort_pointer func, Algorithm* Algo, int no)
{

    count_ncomp = 0;
    count_assign = 0;

    begin = clock();

    int* target = malloc(size * sizeof(int));
    if (!target)
        die("Memory error.");

    memcpy(target, data, size * sizeof(int));

    int* working_array = calloc(size, sizeof(int));
    if (!working_array)
        die("Memory error.");

    func(target, working_array, size);

    Iteration* Iter = malloc(sizeof(Iteration));
    Iter->no = no;

    if (is_sorted(target, size)) {
        end = clock();
        clocks = (double)(end - begin);
        time_spent = clocks / CLOCKS_PER_SEC;

        Iter->is_sorted = 1;
        Iter->comp_count = count_ncomp;
        Iter->assign_count = count_assign;
        Iter->clocks_total = clocks;
        Iter->time_spent = time_spent;
    } else {
        Iter->is_sorted = 0;
    }

    Algo->iterations[no - 1] = Iter;

    free(target);
}

void print_algo(Algorithm* Algo)
{

    printf("Algorithm type: %s\n", Algo->type);
    printf("Time complexity: %s\n", Algo->complexity);
    printf("----------------------------------\n");
    for (int i = 0; i < array_count; i++) {
        if (!Algo->iterations[i]->is_sorted) {
            printf("Not sorted");
        } else {
            printf("no: %d\n", Algo->iterations[i]->no);
            printf("is_sorted: True\n");
            printf("comp_count: %d\n", Algo->iterations[i]->comp_count);
            printf("assign count: %d\n", Algo->iterations[i]->assign_count);
            printf("clocks total: %f\n", Algo->iterations[i]->clocks_total);
            printf("time spent: %f\n", Algo->iterations[i]->time_spent);
        }
        printf("----------------------------------\n");
    }
    printf("Iteration count: %d\n", Algo->iter_count);
    printf("Average compare count: %d\n", Algo->avg_comp);
    printf("Average assign count: %d\n", Algo->avg_assign);
    printf("Average clocks: %f\n", Algo->avg_clocks);
    printf("Average time spent: %f\n", Algo->avg_time);

    printf("===================================\n");
}

void calculate_average(Algorithm* Algo)
{
    int sum_comp = 0;
    int sum_assign = 0;
    double sum_clocks = 0;
    double sum_time = 0;
    int sorted_count = array_count;

    for (int i = 0; i < array_count; i++) {
        if (!Algo->iterations[i]->is_sorted) {
            sorted_count--;
        } else {
            sum_comp += Algo->iterations[i]->comp_count;
            sum_assign += Algo->iterations[i]->assign_count;
            sum_clocks += Algo->iterations[i]->clocks_total;
            sum_time += Algo->iterations[i]->time_spent;
        }
    }

    Algo->avg_comp = sum_comp / sorted_count;
    Algo->avg_assign = sum_assign / sorted_count;
    Algo->avg_clocks = (double)(sum_clocks / sorted_count);
    Algo->avg_time = (double)(sum_time / sorted_count);
    Algo->iter_count = sorted_count;
}

Algorithm** rank_algorithms(Algorithm** target, int first, int last)
{

    Algorithm* temp;
    int pivot, j, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (
                target[i]->avg_time <= target[pivot]->avg_time && i < last) {
                i++;
            }
            while (target[j]->avg_time > target[pivot]->avg_time) {
                j--;
            }
            if (i < j) {
                temp = target[i];
                target[i] = target[j];
                target[j] = temp;
            }
        }

        temp = target[pivot];
        target[pivot] = target[j];
        target[j] = temp;

        rank_algorithms(target, first, j - 1);
        rank_algorithms(target, j + 1, last);
    }
    return target;
}

