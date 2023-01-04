/* Unit tests for sorting algorithms (more will be added for binary
   tree and heap algorithms). */
#include "algorithm.h"
#include <assert.h>

#define TEST_ARR_SIZE 1000

#define TEST_SORTFUNC_INIT(name)                     \
    void test_##name() {                             \
        size_t i;                                    \
        int arr[TEST_ARR_SIZE];                      \
        for (i = 0; i < TEST_ARR_SIZE; ++i)          \
            arr[i] = rand();                         \
        name(arr, TEST_ARR_SIZE, sizeof(int), cmpi); \
        for (i = 0; i < TEST_ARR_SIZE-1; ++i)        \
            assert(arr[i] <= arr[i+1]);              \
    }

TEST_SORTFUNC_INIT(imergesort);
TEST_SORTFUNC_INIT(insertsort);
TEST_SORTFUNC_INIT(heapsort);
TEST_SORTFUNC_INIT(selectsort);
TEST_SORTFUNC_INIT(bubblesort);
TEST_SORTFUNC_INIT(quicksort);

void test_min() {
    int res, arr[10] = {3, 1, 199, 32, -17, 64, 12, 9, 111, 13};
    res = *(int *) min(arr, 10, sizeof(int), cmpi);
    assert(res == -17);
}

void test_max() {
    int res, arr[10] = {3, 1, 199, 32, -17, 64, 12, 9, 111, 13};
    res = *(int *) max(arr, 10, sizeof(int), cmpi);
    assert(res == 199);
}

void test_binsearch() {
    int64_t index;
    int arr[] = {1, 2, 4, 5, 8, 13, 24, 71};
    index = binsearch(arr, 8, sizeof(int), cmpi, (void *) 24);
    assert(index == 6);
    index = binsearch(arr, 8, sizeof(int), cmpi, (void *) 47);
    assert(index == -1);
}

int main() {
    // Test min and max functions.
    test_min();
    test_max();
    // Test sorting functions.
    test_imergesort();
    test_insertsort();
    test_selectsort();
    test_bubblesort();
    test_quicksort();
    // Test binary heap functions (more to be added).
    test_heapsort();
    // Test binary search tree functions (more to be added).
    test_binsearch();
    return 0;
}
