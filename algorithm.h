/* Type generic searching and sorting algorithms in C. */

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef int cmpfunc(const void *, const void *);  // Comparison function.
typedef int keyfunc(const void *);                // Key function.

void *mergesort(const void *data, size_t len, size_t size, cmpfunc cmp);

// Inplace Sorting Algorithms.

void bubblesort(void *data, size_t len, size_t size, cmpfunc cmp);
void selectsort(void *data, size_t len, size_t size, cmpfunc cmp);
void insertsort(void *data, size_t len, size_t size, cmpfunc cmp);
void quicksort(void *data, size_t len, size_t size, cmpfunc cmp);

// Binary Heap Algorithms.

void siftup(void *data, size_t len, size_t size, cmpfunc cmp, size_t start, size_t end);
void siftdown(void *data, size_t len, size_t size, cmpfunc cmp, size_t start, size_t end);
void heapify(void *data, size_t len, size_t size, cmpfunc cmp);
void heapsort(void *data, size_t len, size_t size, cmpfunc cmp);

// Binary Search Tree Algorithms.

int64_t binsearch(const void *data, size_t len, size_t size, cmpfunc cmp, const void *value);
void binsert(void *data, size_t *len, size_t size, cmpfunc cmp, const void *value);
void binserts(void *data, size_t *len, size_t size, cmpfunc cmp, const void *value);
void binremove(void *data, size_t *len, size_t size, cmpfunc cmp, const void *value);

// Comparison Functions.

int cmpc(const void *a, const void *b);
int cmps(const void *a, const void *b);
int cmpi(const void *a, const void *b);
int cmpl(const void *a, const void *b);
int cmpll(const void *a, const void *b);

int cmpf(const void *a, const void *b);
int cmpd(const void *a, const void *b);
int cmpld(const void *a, const void *b);

int cmpuc(const void *a, const void *b);
int cmpus(const void *a, const void *b);
int cmpu(const void *a, const void *b);
int cmpul(const void *a, const void *b);
int cmpull(const void *a, const void *b);
#endif  // ALGORITHM_H
