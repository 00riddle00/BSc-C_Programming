/* Compiler: gcc */
/* CFLAGS=-Wall -xc -g */

/* Paaiškinimai
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
 g) quicksort (greitojo rikiavimo) algoritmas
 h) Įterpimo metodas (angl. insertion sort)
 i) Išrinkimo metodas (angl. selection sort)
 j) Sąlajos metodas (angl. merge sort)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dbg.h"

#define MAX_ITER 100
#define MAX_ALGO 100

int* bubble_sort_a(int* data, int size);
int* bubble_sort_b(int* data, int size);
int* bubble_sort_c(int* data, int size);
int* bubble_sort_d(int* data, int size);
int* bubble_sort_e(int* data, int size);
int* bubble_sort_f(int* data, int size);
int* bubble_sort_b_and_c(int* data, int size);
int* bubble_sort_b_and_e(int* data, int size);
int* bubble_sort_b_and_f(int* data, int size);
int* bubble_sort_c_and_e(int* data, int size);
int* bubble_sort_c_and_f(int* data, int size);
int* bubble_sort_e_and_f(int* data, int size);
int* bubble_sort_b_and_e_and_f(int* data, int size);
int* bubble_sort_b_and_c_and_e_and_f(int* data, int size);

// function which sorts numbers by increasing order,
// using quicksort method.
//
// ::params: x - number array
// ::params: first - index of the first element in the array
// ::params: second - index of the last element in the array
int* quicksort(int* x, int first, int last);
int* insertion_sort(int* data, int size);
int* selection_sort(int* data, int size);

// Merge sort functions (4)
void TopDownMergeSort(int* A, int* B, int n);
void TopDownSplitMerge(int* B, int iBegin, int iEnd, int* A);
void TopDownMerge(int* A, int iBegin, int iMiddle, int iEnd, int* B);
void CopyArray(int* A, int iBegin, int iEnd, int* B);

void getsize(int* size);
int is_sorted(int* data, int size);
void getmemory(int** data, char* ptrName, int size);
void freememory(int** data, char* ptrName);
void filldata(int* data, int size, int min, int max, int repeat);
void print(int* data, int size);
void die();

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

MemoryStats memoryStats;

// How many comparisons are made between neighbor element
int count_ncomp;

// Assignment operation count
int count_assign;

clock_t begin;
clock_t end;

double clocks;
double time_spent;
int array_count;

// a typedef creates a fake type, in this
// case for a function pointer
typedef int* (*sort_pointer)(int* target, int size);

// a typedef creates a fake type, in this
// case for a function pointer
typedef int* (*quicksort_pointer)(int* target, int first, int last);

// a typedef creates a fake type, in this
// case for a function pointer
typedef void (*mergesort_pointer)(int* target, int* working_array, int size);

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_three(int* a, int* b, int* c)
{
    int temp = *a;
    *a = *b;
    *b = *c;
    *c = temp;
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

void test_mergesort(int* data, int size, mergesort_pointer func,
    char* sort_name, char* complexity)
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

    if (is_sorted(target, size)) {
        printf("Sorted by %s\n", sort_name);
        printf("Comp count: %d\n", count_ncomp);
        printf("Assign count: %d\n", count_assign);
    } else {
        printf("ERROR: Not sorted with %s\n", sort_name);
    };

    end = clock();

    clocks = (double)(end - begin);
    time_spent = clocks / CLOCKS_PER_SEC;

    printf("clocks total: %f\n", clocks);
    printf("time spent (sec): %f\n", time_spent);

    printf("algorithm complexity: %s\n", complexity);
    printf("-------------------\n");

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

int main(int argc, char* argv[])
{
    Results* Res = malloc(sizeof(Results));

    Res->date = "2017-12-16";
    Res->arch = "Arch Linux x86_64";
    Res->compiler = "gcc";

    srand(time(NULL));
    // creating algorithm structures
    //
    //
    Algorithm* Algo1 = malloc(sizeof(Algorithm));

    Algo1->type = "bubble_sort_a";
    Algo1->complexity = "O (n^2)";

    Algorithm* Algo2 = malloc(sizeof(Algorithm));

    Algo2->type = "bubble_sort_b";
    Algo2->complexity = "O (n^2)";

    Algorithm* Algo3 = malloc(sizeof(Algorithm));

    Algo3->type = "quicksort";
    Algo3->complexity = "O (nlogn)";

    Res->algorithms[0] = Algo1;
    Res->algorithms[1] = Algo2;
    Res->algorithms[2] = Algo3;

    memoryStats.memJournal = malloc(10 * sizeof(int));

    memoryStats.memUsedByJournal = 10;

    memoryStats.JournalPointerCount = 0;

    printf("Mem used total: %d\n", memoryStats.memUsed);

    int size;
    int min;
    int max;
    int repeat;

    printf("How many arrays would you like to test?");
    if (scanf("%d", &array_count) == 1) {
        printf("Scan successful");
    }

    printf("What is the size of each array?");
    if (scanf("%d", &size) == 1) {
        printf("Scan successful");
    }

    printf("What is the minimum number in each array?");
    if (scanf("%d", &min) == 1) {
        printf("Scan successful");
    }

    printf("What is the maximum number in each array?");
    if (scanf("%d", &max) == 1) {
        printf("Scan successful");
    }

    while (1) {
        printf("How many repeating values there will be AT LEAST?");
        if (scanf("%d", &repeat) == 1 && repeat >= 0
            && repeat <= (max - min + 1)) {
            printf("Scan successful");
            break;
        } else {
            printf("Please enter a non negative integer, not greater than the "
                   "size of the array");
        }
    }

    printf("How many repeating values there will be AT LEAST?");
    if (scanf("%d", &repeat) == 1) {
        printf("Scan successful");
    }

    for (int i = 0; i < array_count; i++) {

        int* data = NULL;

        getmemory(&data, "data", size * sizeof(int));
        if (data == NULL)
            die("Atminties problema");

        filldata(data, size, min, max, repeat);
        if (data == NULL)
            die("Atminties problema");

        print(data, size);
        //---------------------------USING FUNCTION POINTERS-----------------//

        test_sort(data, size, &bubble_sort_a, Algo1, i + 1);
        test_sort(data, size, &bubble_sort_b, Algo2, i + 1);
        /*test_sort(data, size, &bubble_sort_c, "bubble_sort_c", "O(n^2)");*/
        /*test_sort(data, size, &bubble_sort_d, "bubble_sort_d", "O(n^2)");*/
        /*test_sort(data, size, &bubble_sort_e, "bubble_sort_e", "O(n^2)");*/
        /*test_sort(data, size, &bubble_sort_f, "bubble_sort_f", "O(n^2)");*/
        /*test_sort(*/
        /*data, size, &bubble_sort_b_and_c, "bubble_sort_b_and_c", "O(n^2)");*/
        /*test_sort(*/
        /*data, size, &bubble_sort_b_and_e, "bubble_sort_b_and_e", "O(n^2)");*/
        /*test_sort(*/
        /*data, size, &bubble_sort_b_and_f, "bubble_sort_b_and_f", "O(n^2)");*/
        /*test_sort(*/
        /*data, size, &bubble_sort_c_and_e, "bubble_sort_c_and_e", "O(n^2)");*/
        /*test_sort(*/
        /*data, size, &bubble_sort_c_and_f, "bubble_sort_c_and_f", "O(n^2)");*/
        /*test_sort(*/
        /*data, size, &bubble_sort_e_and_f, "bubble_sort_e_and_f", "O(n^2)");*/
        /*test_sort(data, size, &bubble_sort_b_and_e_and_f,*/
        /*"bubble_sort_b_and_c_and_e_and_f", "O(n^2)");*/
        /*test_sort(data, size, &bubble_sort_b_and_c_and_e_and_f,*/
        /*"bubble_sort_b_and_c_and_e_and_f", "O(n^2)");*/

        test_quicksort(data, size, &quicksort, Algo3, i + 1);

        /*test_sort(data, size, &insertion_sort, "insertion sort", "O(2n)");*/
        /*test_sort(data, size, &selection_sort, "selection sort", "O(2n)");*/

        /*test_mergesort(data, size, &TopDownMergeSort, "top down merge
         * sort",*/
        /*"O(n log n)");*/

        free(data);
    }

    calculate_average(Algo1);
    calculate_average(Algo2);
    calculate_average(Algo3);

    for (int i = 0; i < 3; i++) {
        print_algo(Res->algorithms[i]);
    }

    /*print_algo(Algo1);*/
    /*print_algo(Algo2);*/
    /*print_algo(Algo3);*/

    Algorithm** target = malloc(3 * sizeof(Algorithm));

    target[0] = Algo1;
    target[1] = Algo2;
    target[2] = Algo3;

    target = rank_algorithms(target, 0, 2);

    printf("Fastest algorithms (ranking):\n");
    printf("=============================\n");

            for (int i = 0; i < 3; i++)
    {
        printf("%d. ", i+1);
        printf("%s\n", target[i]->type);
        printf("Average time: %f\n", target[i]->avg_time);
        printf("---------------------------------\n");
    }

    printf("Mem used total: %d\n", memoryStats.memUsed);
    free(memoryStats.memJournal);
}

int is_sorted(int* data, int size)
{

    for (int i = 0; i < size; i++) {
        if (i == size - 1)
            break;
        if (data[i] > data[i + 1]) {
            return 0;
        }
    }
    return 1;
}

/**
 * Bubble sort functions (by letter)
 */
int* bubble_sort_a(int* target, int size)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1; j++) {
            if (target[j] > target[j + 1]) {
                swap(&target[j], &target[j + 1]);

                count_assign += 3;
                count_ncomp++;
            }
        }
    }

    return target;
}

int* bubble_sort_b(int* target, int size)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (target[j] > target[j + 1]) {
                swap(&target[j], &target[j + 1]);

                count_ncomp++;
                count_assign += 3;
            }
        }
    }

    return target;
}

int* bubble_sort_c(int* target, int size)
{
    int i = 0;
    int j = 0;
    int count_operations;

    for (i = 0; i < size; i++) {
        if (count_operations == 0)
            break;
        count_operations = 0;
        for (j = 0; j < size - 1; j++) {
            if (target[j] > target[j + 1]) {
                swap(&target[j], &target[j + 1]);

                count_operations++;

                count_ncomp++;
                count_assign += 3;
            }
        }
    }

    return target;
}

int* bubble_sort_d(int* target, int size)
{
    int i = 0;
    int j = 0;

    int last = -1;
    int loops = size - 1;

    for (i = 0; i < size; i++) {
        if (last != -1) {
            loops = last;
        }
        last = 0;
        for (j = 0; j < loops; j++) {
            if (target[j] > target[j + 1]) {
                last = j;

                swap(&target[j], &target[j + 1]);

                count_ncomp++;
                count_assign += 3;
            }
        }
    }

    return target;
}

int* bubble_sort_e(int* target, int size)
{

    int i = 0;
    int j = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1; j++) {
            if (target[j] > target[j + 1]) {
                if (target[j] < target[j + 2]) {
                    swap(&target[j], &target[j + 1]);

                    count_ncomp++;
                    count_assign += 3;
                } else {
                    swap_three(&target[j], &target[j + 1], &target[j + 2]);
                    count_assign += 4;
                }
            }
        }
    }

    return target;
}

int* bubble_sort_f(int* target, int size)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1; j++) {
            if (target[j] > target[j + 1]) {

                swap(&target[j], &target[j + 1]);

                count_ncomp++;
                count_assign += 3;
            }
        }
        for (j = size - 1; j > 0; j--) {
            if (target[j] < target[j - 1]) {
                swap(&target[j], &target[j - 1]);

                count_ncomp++;
                count_assign += 3;
            }
        }
    }

    return target;
}

/**
 * Combined bubble sort functions
 */

int* bubble_sort_b_and_c(int* target, int size)
{
    int i = 0;
    int j = 0;
    int count_operations;

    for (i = 0; i < size; i++) {
        if (count_operations == 0)
            break;
        count_operations = 0;
        for (j = 0; j < size - 1 - i; j++) {
            if (target[j] > target[j + 1]) {
                swap(&target[j], &target[j + 1]);

                count_operations++;

                count_ncomp++;
                count_assign += 3;
            }
        }
    }

    return target;
}

int* bubble_sort_b_and_e(int* target, int size)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (target[j] > target[j + 1]) {
                if (target[j + 1] < target[j + 2]) {
                    swap(&target[j], &target[j + 1]);

                    count_ncomp++;
                    count_assign += 3;
                } else {
                    swap_three(&target[j], &target[j + 1], &target[j + 2]);

                    count_ncomp++;
                    count_assign += 4;
                }
            }
        }
    }

    return target;
}

int* bubble_sort_b_and_f(int* target, int size)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (target[j] > target[j + 1]) {
                swap(&target[j], &target[j + 1]);

                count_ncomp++;
                count_assign += 3;
            }
        }
        for (j = size - 2 - i; j > 0; j--) {
            if (target[j] < target[j - 1]) {
                swap(&target[j], &target[j - 1]);

                count_ncomp++;
                count_assign += 3;
            }
        }
    }

    return target;
}

int* bubble_sort_c_and_e(int* target, int size)
{
    int i = 0;
    int j = 0;

    int count_operations;

    for (i = 0; i < size; i++) {
        if (count_operations == 0)
            break;
        count_operations = 0;
        for (j = 0; j < size - 1; j++) {
            if (target[j] > target[j + 1]) {
                if (target[j + 1] < target[j + 2]) {
                    count_operations++;

                    swap(&target[j], &target[j + 1]);

                    count_ncomp++;
                    count_assign += 3;
                } else {
                    swap_three(&target[j], &target[j + 1], &target[j + 2]);

                    count_operations++;

                    count_ncomp++;
                    count_assign += 4;
                }
            }
        }
    }

    return target;
}

int* bubble_sort_c_and_f(int* target, int size)
{
    int i = 0;
    int j = 0;

    int count_operations;

    for (i = 0; i < size; i++) {
        if (count_operations == 0)
            break;
        count_operations = 0;
        for (j = 0; j < size - 1; j++) {
            if (target[j] > target[j + 1]) {
                swap(&target[j], &target[j + 1]);

                count_operations++;

                count_ncomp++;
                count_assign += 3;
            }
        }
        for (j = size - 1; j > 0; j--) {
            if (target[j] < target[j - 1]) {
                swap(&target[j], &target[j - 1]);

                count_operations++;

                count_ncomp++;
                count_assign += 3;
            }
        }
    }

    return target;
}

int* bubble_sort_e_and_f(int* target, int size)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1; j++) {
            if (target[j] > target[j + 1]) {
                if (target[j] < target[j + 2]) {
                    swap(&target[j], &target[j + 1]);

                    count_ncomp++;
                    count_assign += 3;
                } else {
                    swap_three(&target[j], &target[j + 1], &target[j + 2]);

                    count_assign += 4;
                }
            }
        }
        for (j = size - 1; j > 0; j--) {
            if (target[j] < target[j - 1]) {

                count_ncomp++;

                if (target[j] > target[j - 2]) {
                    swap(&target[j], &target[j - 1]);

                    count_ncomp++;
                    count_assign += 3;
                } else {
                    swap_three(&target[j], &target[j - 1], &target[j - 2]);

                    count_assign += 4;
                }
            }
        }
    }

    return target;
}

int* bubble_sort_b_and_e_and_f(int* target, int size)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (target[j] > target[j + 1]) {
                if (target[j] < target[j + 2]) {
                    swap(&target[j], &target[j + 1]);

                    count_ncomp++;
                    count_assign += 3;
                } else {
                    swap_three(&target[j], &target[j + 1], &target[j + 2]);

                    count_assign += 4;
                }
            }
        }
        for (j = size - 2 - i; j > 0; j--) {
            if (target[j] < target[j - 1]) {

                count_ncomp++;

                if (target[j] > target[j - 2]) {
                    swap(&target[j], &target[j - 1]);

                    count_ncomp++;
                    count_assign += 3;
                } else {
                    swap_three(&target[j], &target[j - 1], &target[j - 2]);

                    count_assign += 4;
                }
            }
        }
    }

    return target;
}

int* bubble_sort_b_and_c_and_e_and_f(int* target, int size)
{
    int i = 0;
    int j = 0;

    int count_operations;

    for (i = 0; i < size; i++) {
        if (count_operations == 0)
            break;
        count_operations = 0;
        for (j = 0; j < size - 1 - i; j++) {
            if (target[j] > target[j + 1]) {

                count_ncomp++;
                count_operations++;

                if (target[j] < target[j + 2]) {
                    swap(&target[j], &target[j + 1]);

                    count_ncomp++;
                    count_assign += 3;
                } else {
                    swap_three(&target[j], &target[j + 1], &target[j + 2]);

                    count_assign += 4;
                }
            }
        }
        for (j = size - 2 - i; j > 0; j--) {
            if (target[j] < target[j - 1]) {

                count_ncomp++;
                count_operations++;

                if (target[j] > target[j - 2]) {
                    swap(&target[j], &target[j - 1]);

                    count_ncomp++;
                    count_assign += 3;
                } else {
                    swap_three(&target[j], &target[j - 1], &target[j - 2]);

                    count_assign += 4;
                }
            }
        }
    }

    return target;
}

int* quicksort(int* target, int first, int last)
{
    int pivot, j, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        count_assign += 3;

        while (i < j) {
            while (target[i] <= target[pivot] && i < last) {
                i++;

                count_ncomp += 2;
            }
            while (target[j] > target[pivot]) {
                j--;

                count_ncomp++;
            }
            if (i < j) {
                swap(&target[i], &target[j]);

                count_assign += 3;
            }
        }

        swap(&target[pivot], &target[j]);

        quicksort(target, first, j - 1);
        quicksort(target, j + 1, last);

        count_assign += 3;
    }
    return target;
}

int* insertion_sort(int* target, int size)
{
    int i = 1;
    int j;
    while (i < size) {
        j = i;
        while (j > 0 && target[j - 1] > target[j]) {
            swap(&target[j], &target[j - 1]);
            j--;

            count_ncomp++;
            count_assign += 3;
        }
        i++;
    }
    return target;
}

int* selection_sort(int* target, int size)
{
    int i, j;
    /* target[0] to target[size-1] is the array to sort */
    for (j = 0; j < size - 1; j++) {
        /* find the min element in the unsorted target[j .. size-1] */
        /* assume the min is the first element */
        int iMin = j;
        count_assign++;
        /* test against elements after j to find the smallest */
        for (i = j + 1; i < size; i++) {
            /* if this element is less, then it is the new minimum */
            if (target[i] < target[iMin]) {
                /* found new minimum; remember its index */
                iMin = i;

                count_ncomp++;
                count_assign++;
            }
        }
        if (iMin != j) {
            swap(&target[j], &target[iMin]);

            count_assign += 3;
        }
    }
    return target;
}

//------------------------------MERGE SORT-----------------------------/

// Array A[] has the items to sort; array B[] is a work array.
void TopDownMergeSort(int* A, int* B, int n)
{
    CopyArray(A, 0, n, B);         // duplicate array A[] into B[]
    TopDownSplitMerge(B, 0, n, A); // sort data from B[] into A[]
}

// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge(int* B, int iBegin, int iEnd, int* A)
{

    int iMiddle;
    if (iEnd - iBegin < 2) { // if run size == 1
        return;              //   consider it sorted
    }
    // split the run longer than 1 item into halves
    iMiddle = (iEnd + iBegin) / 2; // iMiddle = mid point
    count_assign++;
    // recursively sort both runs from array A[] into B[]
    TopDownSplitMerge(A, iBegin, iMiddle, B); // sort the left  run
    TopDownSplitMerge(A, iMiddle, iEnd, B);   // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge(B, iBegin, iMiddle, iEnd, A);
}

//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge(int* A, int iBegin, int iMiddle, int iEnd, int* B)
{
    int i, j, k;
    i = iBegin, j = iMiddle;
    count_assign += 2;

    // While there are elements in the left or right runs...
    for (k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            i = i + 1;

            count_ncomp += 3;
            count_assign++;
        } else {
            B[k] = A[j];
            j = j + 1;

            count_assign++;
        }
    }
}

void CopyArray(int* A, int iBegin, int iEnd, int* B)
{
    int k;

    for (k = iBegin; k < iEnd; k++) {
        B[k] = A[k];

        count_assign++;
    }
}

//-----------------------------/-MERGE SORT-----------------------------/

void getsize(int* size) { scanf("%d", size); }

void getmemory(int** data, char* ptrName, int memory_size)
{

    int exists = 0;

    for (int i = 0; i < memoryStats.JournalPointerCount; i++) {
        if (memoryStats.memJournal[i].pointerName == ptrName) {
            memoryStats.memJournal[i].pointerMemory += memory_size;
            exists = 1;
            break;
        }
    }

    if (!exists) {
        memoryStats.memJournal[memoryStats.JournalPointerCount++].pointerName
            = ptrName;
        memoryStats.memJournal[memoryStats.JournalPointerCount].pointerMemory
            = memory_size;
    }

    memoryStats.memUsed += memory_size;

    *data = malloc(memory_size);
}

void freememory(int** data, char* ptrName)
{

    for (int i = 0; i < memoryStats.JournalPointerCount; i++) {
        if (memoryStats.memJournal[i].pointerName == ptrName) {
            memoryStats.memUsed -= memoryStats.memJournal[i].pointerMemory;
            memoryStats.memJournal[i].pointerMemory = 0;
            break;
        }
    }

    free(*data);
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

void print(int* data, int size)
{
    int i;
    printf("Jūsų sugeneruoti skaičiai:\n");
    for (i = 0; i < size; i++) {
        printf("%d\n", data[i]);
    }
}

void die(char* message)
{
    printf("%s\n", message);
    exit(1);
}
