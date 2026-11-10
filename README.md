# Group 4 — Programming Assignment 3

## Team Members

- Bhavesh Malhi
- Erik Elizarraras
- Jimmy Williams
- Kevin Xiao
- Saif Al Habashneh

## Description

This C program uses POSIX threads to sort and merge an array of 11 integers.
Two sorting threads use insertion sort to sort separate subarrays of 5 and 6
elements in place. After both sorting threads finish, a third thread merges
the sorted subarrays into the result array. The program prints the original
array and the final sorted array and checks every thread creation and join
for errors.

## Build and Run

```sh
gcc -Wall -Wextra -pthread sorting.c -o sorting
./sorting | tee sorting_output.txt
```

Expected output:

```text
Unsorted array: 7 12 19 3 18 4 2 -5 6 15 8
Final sorted array: -5 2 3 4 6 7 8 12 15 18 19
```

## Files

- `sorting.c`: Complete sorting and merging program.
- `sorting_output.txt`: Output captured from the final program.
