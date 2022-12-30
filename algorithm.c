#include "algorithm.h"

#define VOIDSWAP(tmp, x, y, size) {\
    memcpy(tmp, x, size);          \
    memcpy(x, y, size);            \
    memcpy(y, tmp, size);          \
}

/* Including <stdlib.h> defines both min and max macros,
   so undefining them allows the appropriate function
   names to be used. */
#undef min
#undef max

void *min(void *data, size_t len, size_t size, cmpfunc cmp) {
    size_t i;
    void *tmp, *min_val;
    min_val = ((char *) data);  // Assume the first item in the array is the minimum.
    for (i = 1; i < len; ++i) {
        tmp = ((char *) data) + i * size;
        min_val = (cmp(tmp, min_val) < 0) ? tmp : min_val;
    }
    return min_val;
}

void *max(void *data, size_t len, size_t size, cmpfunc cmp) {
    size_t i;
    void *tmp, *max_val;
    max_val = ((char *) data);  // Assume the first item in the array is the maximum.
    for (i = 1; i < len; ++i) {
        tmp = ((char *) data) + i * size;
        max_val = (cmp(tmp, max_val) > 0) ? tmp : max_val;
    }
    return max_val;
}

void *min_k(void *data, size_t len, size_t size, keyfunc key) {
    size_t i;
    void *tmp, *min_val;
    min_val = ((char *) data);  // Assume the first item in the array is the minimum.
    for (i = 1; i < len; ++i) {
        tmp = ((char *) data) + i * size;
        min_val = (key(tmp) < key(min_val)) ? tmp : min_val;
    }
    return min_val;
}

void *max_k(void *data, size_t len, size_t size, keyfunc key) {
    size_t i;
    void *tmp, *max_val;
    max_val = ((char *) data);  // Assume the first item in the array is the maximum.
    for (i = 1; i < len; ++i) {
        tmp = ((char *) data) + i * size;
        max_val = (key(tmp) > key(max_val)) ? tmp : max_val;
    }
    return max_val;
}

static void *merge(void *left, size_t llen, void *right, size_t rlen, size_t size, cmpfunc cmp) {
    /* The code below was partially borrowed from https://youtu.be/4VqmGXwpLqc
       with a few modifications.

       Namely, instead of removing items from either the left or right arrays,
       (which would incur a cost that is linear to the size of the array itself
       since a call to memmove would be made), an index was used and advanced
       based on which element has been processed. This is equivalent since the
       order of the remaining elements in the array don't change. */
    size_t i, j, k;
    void *merged, *lval, *rval;
    merged = malloc((llen + rlen) * size);
    i = j = 0;
    /* While there are elements in both the left and right
       subarrays to process, compare elements from both,
       and decide which to add to the new merged array copy. */
    for (k = 0; i < llen && j < rlen; ++k) {
        lval = ((char *) left) + i * size;      //  left[i]
        rval = ((char *) right) + j * size;     // right[j]
        /* If data[i] < data[j], then advance one element forward
           on the left subarray (by incrementing the index), and
           continue the loop. Otherwise, advance one element forward
           on the right subarray. */
        if (cmp(lval, rval) < 0) {
            memcpy(((char *) merged) + k * size, lval, size);
            ++i;
        } else {
            memcpy(((char *) merged) + k * size, rval, size);
            ++j;
        }
    }
    /* While there are elements left to process in the left
       array, add them to the merged array. */
    while (i < llen) {
        lval = ((char *) left) + i * size;
        memcpy(((char *) merged) + k * size, lval, size);
        ++i;
        ++k;
    }
    /* While there are elements left to process in the right
       array, add them to the merged array. */
    while (j < rlen) {
        rval = ((char *) right) + j * size;
        memcpy(((char *) merged) + k * size, rval, size);
        ++j;
        ++k;
    }
    // Free both subarrays to avoid memory leak.
    free(left);
    free(right);
    return merged;
}

void *mergesort(const void *data, size_t len, size_t size, cmpfunc cmp) {
    size_t mid, llen, rlen;
    void *left, *right;
    if (len == 1) {
        void *copy;
        copy = malloc(len * size);
        memcpy(copy, data, len * size);
        return copy;
    }
    // Calculate left and right array lengths.
    mid = len / 2;
    llen = mid;
    rlen = mid + (len & 1);  // Right subarray is bigger if length is odd.
    // Make left and right subarray copies.
    left = malloc(llen * size);
    right = malloc(rlen * size);
    memcpy(left, data, llen * size);
    memcpy(right, ((char *) data) + llen * size, rlen * size);
    // Recursive step.
    left = mergesort(left, llen, size, cmp);
    right = mergesort(right, rlen, size, cmp);
    return merge(left, llen, right, rlen, size, cmp);
}

void bubblesort(void *data, size_t len, size_t size, cmpfunc cmp) {
    size_t i, j;
    void *a, *b, *tmp;
    tmp = malloc(size);
    for (i = 1; i < len; ++i) {
        for (j = 0; j < len - 1; ++j) {
            a = ((char *) data) + j * size;        // data[j]
            b = ((char *) data) + (j + 1) * size;  // data[j+1]
            // If data[j] < data[j+1], then swap data[j] and data[j+1].
            if (cmp(a, b) > 0)
                VOIDSWAP(tmp, a, b, size);
        }
    }
    free(tmp);
}

void selectsort(void *data, size_t len, size_t size, cmpfunc cmp) {
    size_t min, i, j;
    void *a, *b, *tmp;
    tmp = malloc(size);
    for (j = 0; j < len - 1; ++j) {
        min = j;
        for (i = j + 1; i < len; ++i) {
            a = ((char *) data) + i * size;
            b = ((char *) data) + min * size;
            // If data[i] < data[min], then min = i.
            if (cmp(a, b) < 0)
                min = i;
        }
        if (min != j) {
            a = ((char *) data) + j * size;
            b = ((char *) data) + min * size;
            // Swap data[min] and data[j].
            VOIDSWAP(tmp, a, b, size);
        }
    }
    free(tmp);
}

void insertsort(void *data, size_t len, size_t size, cmpfunc cmp) {
    size_t i, j;
    void *a, *b, *tmp;
    tmp = malloc(size);
    for (i = 1; i < len; ++i) {
        j = i;
        a = ((char *) data) + (j - 1) * size;      // data[j-1]
        b = ((char *) data) + j * size;            // data[j]
        while (j > 0 && cmp(a, b) > 0) {
            VOIDSWAP(tmp, a, b, size);
            --j;
            a = ((char *) data) + (j - 1) * size;  // data[j-1]
            b = ((char *) data) + j * size;        // data[j]
        }
    }
    free(tmp);
}

static size_t partition(void *data, size_t len, size_t size, cmpfunc cmp, int lo, int hi) {
    size_t i, j;
    void *a, *b, *pivot, *tmp;
    pivot = ((char *) data) + hi * size;
    i = lo - 1;
    tmp = malloc(size);
    for (j = lo; j < hi; ++j) {
        a = ((char *) data) + j * size;        // data[j]
        /* If data[j] is less than or equal to the pivot element,
           then swap data[i+1] and data[j]. */
        if (cmp(a, pivot) <= 0) {
            a = ((char *) data) + ++i * size;  // data[i+1]
            b = ((char *) data) + j * size;    // data[j]
            VOIDSWAP(tmp, a, b, size);
        }
    }
    a = ((char *) data) + ++i * size;          // data[i+1]
    b = ((char *) data) + hi * size;           // data[hi]
    VOIDSWAP(tmp, a, b, size);
    free(tmp);
    return i;
}

static void _quicksort(void *data, size_t len, size_t size, cmpfunc cmp, int lo, int hi) {
    size_t p;
    if (lo >= hi || lo < 0)
        return;
    p = partition(data, len, size, cmp, lo, hi);
    _quicksort(data, len, size, cmp, lo, p - 1);
    _quicksort(data, len, size, cmp, p + 1, hi);
}

void quicksort(void *data, size_t len, size_t size, cmpfunc cmp) {
    _quicksort(data, len, size, cmp, 0, len - 1);
}

// Binary Heap Implementation.

// Reference: https://en.wikipedia.org/wiki/Heapsort

#define PARENT(i) ((i-1) / 2)
#define LEFTCHILD(i) (2*i + 1)
#define RIGHTCHILD(i) (2*i + 2)

void siftup(void *data, size_t len, size_t size, cmpfunc cmp, size_t start, size_t end) {
    size_t child, parent;
    void *a, *b, *tmp;
    child = end;
    tmp = malloc(size);
    while (child > start) {
        parent = PARENT(child);
        a = ((char *) data) + parent * size;
        b = ((char *) data) + child * size;
        if (cmp(a, b) >= 0)
            break;
        VOIDSWAP(tmp, a, b, size);
        child = parent;
    }
    free(tmp);
}

void siftdown(void *data, size_t len, size_t size, cmpfunc cmp, size_t start, size_t end) {
    size_t child, root, swap;
    void *a, *b, *tmp;
    root = start;
    tmp = malloc(size);
    while (LEFTCHILD(root) <= end) {
        child = LEFTCHILD(root);
        swap = root;
        a = ((char *) data) + swap * size;        // data[swap]
        b = ((char *) data) + child * size;       // data[child]
        // If data[swap] < data[child], then swap = child.
        if (cmp(a, b) < 0)
            swap = child;
        b = ((char *) data) + (child + 1) * size; // data[child+1]
        /* If child + 1 <= end and data[swap] < data[child],
           then swap = child + 1 */
        if (child + 1 <= end && cmp(a, b) < 0)
            swap = child + 1;
        if (swap == root)
            break;
        a = ((char *) data) + root * size;
        b = ((char *) data) + swap * size;
        // Swap data[root] and data[swap].
        VOIDSWAP(tmp, a, b, size);
        root = swap;
    }
    free(tmp);
}

void heapify(void *data, size_t len, size_t size, cmpfunc cmp) {
    size_t end;
    for (end = 1; end < len; ++end)
        siftup(data, len, size, cmp, 0, end);
}

void heapsort(void *data, size_t len, size_t size, cmpfunc cmp) {
    size_t end;
    void *a, *b, *tmp;
    heapify(data, len, size, cmp);
    a = ((char *) data);
    tmp = malloc(size);
    for (end = len - 1; end > 0; --end) {
        b = ((char *) data) + end * size;   // data[end]
        VOIDSWAP(tmp, a, b, size);          // Swap data[0] and data[end].
        heapify(data, end, size, cmp);
    }
    free(tmp);
}

int64_t binsearch(const void *data, size_t len, size_t size, cmpfunc cmp, const void *value) {
    /* The following code comes from K & R The C Programming Language,
       with a few modifications. */
    size_t lo, hi, mid;
    int key;
    void *item;
    lo = 0;
    hi = len - 1;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        item = ((char *) data) + mid * size;
        key = cmp(&value, item);
        if (key < 0)
            hi = mid - 1;
        else if (key > 0)
            lo = mid + 1;
        else
            return mid;
    }
    return -1;  // Element not in array.
}

static size_t find_index(const void *data, size_t len, size_t size, cmpfunc cmp, const void *value) {
    /* The following code is based on the bisect module
       in the Python Standard Library (see bisect_right). */
    size_t lo, hi, mid;
    int key;
    void *item;
    lo = 0;
    hi = len - 1;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        item = ((char *) data) + mid * size;
        key = cmp(&value, item);
        if (key < 0)
            hi = mid - 1;
        else if (key > 0)
            lo = mid + 1;
    }
    return lo;
}

// The code for the insertion functions are my own.

void binsert(void *data, size_t *len, size_t size, cmpfunc cmp, const void *value) {
    size_t index;
    void *src, *dst;
    index = find_index(data, *len, size, cmp, value);
    src = ((char *) data) + index * size;
    dst = ((char *) data) + (index + 1) * size;
    /* Move all elements at the index or after one position
       to the right, and then insert the specified element. */
    memmove(dst, src, ((*len)++ - index) * size);
    memcpy(((char *) data) + index * size, value, size);
}

void binserts(void *data, size_t *len, size_t size, cmpfunc cmp, const void *value) {
    size_t index;
    void *src, *dst;
    index = find_index(data, *len, size, cmp, value);
    src = ((char *) data) + index * size;
    dst = ((char *) data) + (index + 1) * size;
    data = realloc(data, ((*len) + 1) * size);  // Reallocate for additional element.
    /* Move all elements at the index or after one position
       to the right, and then insert the specified element. */
    memmove(dst, src, ((*len)++ - index) * size);
    memcpy(((char *) data) + index * size, value, size);
}

void binremove(void *data, size_t *len, size_t size, cmpfunc cmp, const void *value) {
    int64_t index;
    void *src, *dst;
    index = binsearch(data, *len, size, cmp, value);  // Find element index.
    if (index == -1)
        return;
    src = ((char *) data) + (index + 1) * size;
    dst = ((char *) data) + index * size;
    /* Moving elements one position to the left automatically
       overwrites the old value. */
    memmove(dst, src, ((*len)-- - index - 1) * size);
}

// Comparison Functions.

// Type generic comparison (works for unsigned, int, and float types).
// (Yes, I was too lazy to manually type each comparison function).

#define CMPFUNC_INIT(name, type)            \
    int name(const void *a, const void *b) {\
        type x, y;                          \
        x = *(type *) a;                    \
        y = *(type *) b;                    \
        if (x < y)                          \
            return -1;                      \
        if (x > y)                          \
            return 1;                       \
        return 0;                           \
    }

// Signed Integer Comparisons.

CMPFUNC_INIT(cmpc, char);
CMPFUNC_INIT(cmps, short);
CMPFUNC_INIT(cmpi, int);
CMPFUNC_INIT(cmpl, long);
CMPFUNC_INIT(cmpll, long long);

// Floating Point Comparisons.

CMPFUNC_INIT(cmpf, float);
CMPFUNC_INIT(cmpd, double);
CMPFUNC_INIT(cmpld, long double);

// Unsigned Integer Comparisons.

CMPFUNC_INIT(cmpuc, unsigned char);
CMPFUNC_INIT(cmpus, unsigned short);
CMPFUNC_INIT(cmpu, unsigned int);
CMPFUNC_INIT(cmpul, unsigned long);
CMPFUNC_INIT(cmpull, unsigned long long);

/* It might be worth redefining a key function to return
   a 64-bit integer to allow for all types to work. */

int keyi(const void *x) {
    return *(int *) x;
}
