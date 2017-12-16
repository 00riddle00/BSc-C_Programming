/* Compiler: gcc */
/* CFLAGS=-Wall -xc -g */

/* Version: 0.0 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void actions(int *rawArray, int size);


int main(int argc, char *argv[]) {
    srand(time(NULL));

    char *capacity_message = "input capacity:";
    int *rawArray;
    int capacity;
    int size;

    while (1) {
        printf("%s\n", capacity_message);

        if (scanf("%d", &capacity) == 1 && getchar() == '\n') {
            if (capacity < 1) {
                printf("capacity should be greater than zero\n");
            } else {
                rawArray = calloc(capacity, sizeof(int));
                printf("OK\n");
                printf("your template array:\n");
                printf("[ ");
                for (int i = 0; i < capacity; ++i) {
                    printf("%d ", rawArray[i]);
                }
                printf("]\n");
                break;
            }
        } else {
            printf("Invalid action, only integer is accepted\n");
            while (getchar() != '\n');
        }
    }

    char *size_message = "input size:";

    while (1) {
        printf("%s\n", size_message);

        if (scanf("%d", &size) == 1 && getchar() == '\n') {
            if (size < 1) {
                printf("size should be greater than zero\n");
            } else {
                for (int i = 0; i < size; ++i) {
                    rawArray[i] = rand() % 10;
                }

                printf("your generated array:\n");
                printf("[ ");

                for (int i = 0; i < size; ++i) {
                    printf("%d ", rawArray[i]);
                }

                printf("]\n");
                break;
            }
        } else {
            printf("Invalid action, only integer is accepted\n");
            while (getchar() != '\n');
        }
    }

    actions(rawArray, size);

    return 0;
}

void actions(int *rawArray, int size) {

    char *action_message = "your action:";
    char *action_word;
    int pos;
    int number;

    while (1) {
        printf("%s\n", action_message);

        int max_params = 3;

        char **params = NULL;
        params = calloc(max_params, max_params * sizeof(char *));
        if (params == NULL) exit(1);

        char *pch;
        int count;

        char line[100];

        fgets(line, sizeof(line), stdin);

        count = 0;

        pch = strtok(line, " \n");
        while (pch != NULL) {
            if (count < 3) {
                params[count] = pch ? strdup(pch) : pch;
                if (!pch) exit(1);
            }

            pch = strtok(NULL, " \n");
            count++;
        }

        action_word = params[0];

        if (params[1] != NULL) {
            pos = atoi(params[1]);
        }

        if (params[2] != NULL) {
            number = atoi(params[2]);
        }

        
        if (!strcmp(action_word, "delete")) {
            printf("Success!\n");
            rawArray[pos] = 0;
            for (int i = pos; i < size-1; ++i) {
                rawArray[i] = rawArray[i+1];
            }
            --size;

            printf("Your modified array:\n");
            printf("[ ");
            for (int i = 0; i < size; ++i) {
                printf("%d ", rawArray[i]);
            }
            printf("]\n");
            break;
        } else if (!strcmp(action_word, "update")) {
            rawArray[pos] = number;

            printf("Your modified array:\n");
            printf("[ ");
            for (int i = 0; i < size; ++i) {
                printf("%d ", rawArray[i]);
            }
            printf("]\n");

            break;
        } else if (!strcmp(action_word, "insert")) {

            for (int i = size; i > pos; --i) {
                rawArray[i] = rawArray[i-1];
            }

            rawArray[pos] = number;
            ++size;

            printf("Your modified array:\n");
            printf("[ ");
            for (int i = 0; i < size; ++i) {
                printf("%d ", rawArray[i]);
            }
            printf("]\n");

            break;
        } else {
            printf("There is no action %s\n", action_word);
            break;
        }
    }
}


