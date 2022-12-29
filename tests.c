/* Unit tests for sorting algorithms (more will be added for bst and heap algorithms). */
#include "algorithm.h"
#include <assert.h>

#define TEST_ARR_SIZE 1000

#define TESTSORTFUNC_INIT(name)                                             \
    void test_##name() {                                                    \
        size_t i;                                                           \
        int arr[TEST_ARR_SIZE];                                             \
        for (i = 0; i < TEST_ARR_SIZE; ++i)                                 \
            arr[i] = rand();                                                \
        name(arr, TEST_ARR_SIZE, sizeof(int), cmpi);                        \
        for (i = 0; i < TEST_ARR_SIZE-1; ++i)                               \
            assert(arr[i] <= arr[i+1]);                                     \
    }

// Convert a non-inplace sorting function to one that is inplace.
#define MAKE_SORTFUNC_INPLACE(name)                                        \
    void name##_inplace(void *data, size_t len, size_t size, cmpfunc cmp) {\
        void *ret = name(data, len, size, cmp);                            \
        memcpy(data, ret, len * size);                                     \
        free(ret);                                                         \
    }

MAKE_SORTFUNC_INPLACE(mergesort);

TESTSORTFUNC_INIT(mergesort_inplace);
TESTSORTFUNC_INIT(insertsort);
TESTSORTFUNC_INIT(heapsort);
TESTSORTFUNC_INIT(selectsort);
TESTSORTFUNC_INIT(bubblesort);
TESTSORTFUNC_INIT(quicksort);

int main() {
    test_mergesort_inplace();
    test_insertsort();
    test_heapsort();
    test_selectsort();
    test_bubblesort();
    test_quicksort();
    return 0;
}
