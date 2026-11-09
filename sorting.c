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

/* Starts both sorting threads, waits for them, then merges and prints the result. */
int main(void) {
    pthread_t left_thread;
    pthread_t right_thread;
    pthread_t merging_thread;
    SubArray left = {unsorted, SIZE / 2};
    SubArray right = {unsorted + SIZE / 2, SIZE - SIZE / 2};
    MergeParams merge_params;
    int status;

    /* These local parameters stay valid until all threads are joined.
     * No dynamic allocation is needed. */
    print_array("Unsorted array:", unsorted, SIZE);

    status = pthread_create(&left_thread, NULL, sort_thread, &left);
    if (status != 0) {
        fprintf(stderr, "Failed to create left sorting thread (error %d).\n", status);
        exit(EXIT_FAILURE);
    }

    status = pthread_create(&right_thread, NULL, sort_thread, &right);
    if (status != 0) {
        fprintf(stderr, "Failed to create right sorting thread (error %d).\n", status);
        exit(EXIT_FAILURE);
    }

    status = pthread_join(left_thread, NULL);
    if (status != 0) {
        fprintf(stderr, "Failed to join left sorting thread (error %d).\n", status);
        exit(EXIT_FAILURE);
    }

    status = pthread_join(right_thread, NULL);
    if (status != 0) {
        fprintf(stderr, "Failed to join right sorting thread (error %d).\n", status);
        exit(EXIT_FAILURE);
    }

    merge_params.left = left;
    merge_params.right = right;

    status = pthread_create(&merging_thread, NULL, merge_thread, &merge_params);
    if (status != 0) {
        fprintf(stderr, "Failed to create merge thread (error %d).\n", status);
        exit(EXIT_FAILURE);
    }

    status = pthread_join(merging_thread, NULL);
    if (status != 0) {
        fprintf(stderr, "Failed to join merge thread (error %d).\n", status);
        exit(EXIT_FAILURE);
    }

    print_array("Final sorted array:", result, SIZE);
    return 0;
}

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
