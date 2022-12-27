// Test file (many more tests will be added later on for each algorithm).

#include "algorithm.h"
#include <assert.h>

int main() {
    int arr[] = {4, 3, 1, 9, 7, 2};
    int *arr2 = mergesort(arr, 6, sizeof(int), cmpi); // Mergesort with integer comparison.
    for (int i = 0; i < 5; ++i)
        assert(arr2[i] <= arr2[i + 1]);
    free(arr2);
    return 0;
}
