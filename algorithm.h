/* Type generic searching and sorting algorithms in C. */

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef int cmpfunc(const void *, const void *);  // Comparison function.

// Min/Max Functions.

#undef min
#undef max

/* Find the minimum value in an array. */
void *min(void *data, size_t len, size_t size, cmpfunc cmp);

/* Find the maximum value in an array. */
void *max(void *data, size_t len, size_t size, cmpfunc cmp);

/* Shuffles the items in an array. */
void shuffle(void *data, size_t len, size_t size);

/* Reverses the items in an array. */
void reverse(void *data, size_t len, size_t size);

/* Checks if an array is sorted. */
bool issorted(void *data, size_t len, size_t size, cmpfunc cmp);

// Non-inplace Sorting Algorithms.

/* Merge sort algorithm (Not inplace). */
void *mergesort(const void *data, size_t len, size_t size, cmpfunc cmp);

// Inplace Sorting Algorithms.

/* Merge sort algorithm inplace (uses an additional memcopy operation). */
void imergesort(void *data, size_t len, size_t size, cmpfunc cmp);

/* Bubble sort algorithm. */
void bubblesort(void *data, size_t len, size_t size, cmpfunc cmp);

/* Selection sort algorithm. */
void selectsort(void *data, size_t len, size_t size, cmpfunc cmp);

/* Insertion sort algorithm. */
void insertsort(void *data, size_t len, size_t size, cmpfunc cmp);

/* Quick sort algorithm. */
void quicksort(void *data, size_t len, size_t size, cmpfunc cmp);

/* Don't use this. */
void bogosort(void *data, size_t len, size_t size, cmpfunc cmp);

// Binary Heap Algorithms.

/* Moves a value up in the heap. */
void siftup(void *data, size_t len, size_t size, cmpfunc cmp, size_t start, size_t end);

/* Moves a value down in the heap. */
void siftdown(void *data, size_t len, size_t size, cmpfunc cmp, size_t start, size_t end);

/* Converts an array to a binary heap (changes ordering). */
void heapify(void *data, size_t len, size_t size, cmpfunc cmp);

/* Heap sort algorithm. */
void heapsort(void *data, size_t len, size_t size, cmpfunc cmp);

// Binary Search Tree Algorithms.

/* Binary Search on an array of data. */
int64_t binsearch(const void *data, size_t len, size_t size, cmpfunc cmp, const void *value);

/* Binary Search Tree Insertion into an array. */
void binsert(void *data, size_t *len, size_t size, cmpfunc cmp, const void *value);

/* Safe Binary Search Tree Insertions into an array (assumes no additional memory allocated) */
void binserts(void *data, size_t *len, size_t size, cmpfunc cmp, const void *value);

/* Binary Search Tree Deletion from an array. */
void binremove(void *data, size_t *len, size_t size, cmpfunc cmp, const void *value);

// Comparison Functions.

/* Compare char. */
int cmpc(const void *a, const void *b);

/* Compare short. */
int cmps(const void *a, const void *b);

/* Compare int. */
int cmpi(const void *a, const void *b);

/* Compare long. */
int cmpl(const void *a, const void *b);

/* Compare long long. */
int cmpll(const void *a, const void *b);

/* Compare float. */
int cmpf(const void *a, const void *b);

/* Compare double. */
int cmpd(const void *a, const void *b);

/* Compare long double. */
int cmpld(const void *a, const void *b);

/* Compare unsigned char. */
int cmpuc(const void *a, const void *b);

/* Compare unsigned short. */
int cmpus(const void *a, const void *b);

/* Compare unsigned int. */
int cmpu(const void *a, const void *b);

/* Compare unsigned long. */
int cmpul(const void *a, const void *b);

/* Compare unsigned long long. */
int cmpull(const void *a, const void *b);
#endif  // ALGORITHM_H
