#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 11

int unsorted[SIZE] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
int result[SIZE];

typedef struct {
    int *start;
    int size;
} SubArray;

typedef struct {
    SubArray left;
    SubArray right;
} MergeParams;

void *sort_thread(void *argument);
void *merge_thread(void *argument);
void print_array(const char *label, const int array[], int size);

/* Prints a label followed by the array values and a newline. */
void print_array(const char *label, const int array[], int size) {
    int index;

    printf("%s", label);
    for (index = 0; index < size; index++) {
        printf(" %d", array[index]);
    }
    printf("\n");
}

/* Sorts this thread's part of the array from smallest to largest.
 * The start pointer and size tell the thread which part is its own. */
void *sort_thread(void *argument) {
    SubArray *part = (SubArray *)argument;
    int *values = part->start;
    int count = part->size;
    int i, j, key;
    
    /* Insertion sort */
    for (i = 1; i < count; i++) {
        key = values[i];
        j = i - 1;

        /* Moves larger values one spot to the right */
        while (j >= 0 && values[j] > key) {
            values[j + 1] = values[j];
            j--;
        }
        values[j + 1] = key;
    }
    return NULL;
}

/* Placeholder for the merging thread implementation. */
void *merge_thread(void *argument) {
    (void)argument;
    return NULL;
}
