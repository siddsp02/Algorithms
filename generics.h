/* Generic algorithm macros for built-in types. */

#ifndef GENERICS_H
#define GENERICS_H
#include "algorithm.h"

#define GETCMP(x) _Generic((x), \
    char: cmpc,                 \
    short: cmps,                \
    int: cmpi,                  \
    long: cmpl,                 \
    long long: cmpll,           \
    float: cmpf,                \
    double: cmpd,               \
    long double: cmpld,         \
    unsigned char: cmpuc,       \
    unsigned short: cmpus,      \
    unsigned int: cmpu,         \
    unsigned long: cmpul,       \
    unsigned long long: cmpull  \
)

#define min(data, len) min(data, len, sizeof(data[0]), GETCMP(data[0]))
#define max(data, len) max(data, len, sizeof(data[0]), GETCMP(data[0]))
#define shuffle(data, len) shuffle(data, len, sizeof(data[0]))
#define reverse(data, len) reverse(data, len, sizeof(data[0]))
#define issorted(data, len) issorted(data, len, sizeof(data[0]), GETCMP[data[0]])

#define mergesort(data, len) mergesort(data, len, sizeof(data[0]), GETCMP(data[0]))

#define imergesort(data, len) imergesort(data, len, sizeof(data[0]), GETCMP(data[0]))
#define quicksort(data, len) quicksort(data, len, sizeof(data[0]), GETCMP(data[0]))
#define bubblesort(data, len) bubblesort(data, len, sizeof(data[0]), GETCMP(data[0]))
#define insertsort(data, len) insertsort(data, len, sizeof(data[0], GETCMP(data[0])))
#define selectsort(data, len) selectsort(data, len, sizeof(data[0]), GETCMP(data[0]))
#define bogosort(data, len) bogosort(data, len, sizeof(data[0]), GETCMP(data[0]))

#define siftup(data, len, start, end) siftup(data, len, sizeof(data[0]), GETCMP(data[0]), start, end)
#define siftdown(data, len, start, end) siftdown(data, len, sizeof(data[0]), GETCMP(data[0]), start, end)
#define heapify(data, len) heapify(data, len, sizeof(data[0]), GETCMP(data[0]))
#define heapsort(data, len) heapsort(data, len, sizeof(data[0]), GETCMP(data[0]))

#define binsearch(data, len, value) binsearch(data, len, sizeof(data[0]), GETCMP(data[0]), (void *) value)
#define binsert(data, len, value) binsert(data, len, sizeof(data[0]), GETCMP(data[0]), (void *) value)
#define binserts(data, len, value) binserts(data, len, sizeof(data[0]), GETCMP(data[0]), (void *) value)
#define binremove(data, len, value) binremove(data, len, sizeof(data[0]), GETCMP(data[0]), (void *) value)
#endif  // GENERICS_H
