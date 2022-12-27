#include "algorithm.h"

#define VOIDSWAP(tmp, x, y, size) {\
    memcpy(tmp, x, size);          \
    memcpy(x, y, size);            \
    memcpy(y, tmp, size);          \
}

static void *merge(void *left, size_t llen, void *right, size_t rlen, size_t size, cmpfunc cmp) {
    size_t i, j, k;
    void *merged, *lval, *rval;
    merged = malloc((llen + rlen) * size);
    i = j = k = 0;
    while (i < llen && j < rlen) {
        lval = ((char *) left) + i * size;
        rval = ((char *) right) + j * size;
        if (cmp(lval, rval) < 0) {
            memcpy(((char *) merged) + k * size, lval, size);
            ++i;
        } else {
            memcpy(((char *) merged) + k * size, rval, size);
            ++j;
        }
        ++k;
    }
    /* While there are elements left to process in the left
       array, add them to the merged array.*/
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
    rlen = mid + (len & 1);
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
    int key;
    void *a, *b, *tmp;
    tmp = malloc(size);
    for (i = 1; i < len; ++i) {
        for (j = 0; j < len - 1; ++j) {
            a = ((char *) data) + j * size;
            b = ((char *) data) + (j + 1) * size;
            key = cmp(a, b);
            if (key > 0)
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
            if (cmp(a, b) < 0)
                min = i;
        }
        if (min != j) {
            a = ((char *) data) + j * size;
            b = ((char *) data) + min * size;
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
        a = ((char *) data) + (j - 1) * size;
        b = ((char *) data) + j * size;
        while (j > 0 && cmp(a, b) > 0) {
            VOIDSWAP(tmp, a, b, size);
            --j;
            a = ((char *) data) + (j - 1) * size;
            b = ((char *) data) + j * size;
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
        a = ((char *) data) + j * size;
        if (cmp(a, pivot) <= 0) {
            a = ((char *) data) + ++i * size;
            b = ((char *) data) + j * size;
            VOIDSWAP(tmp, a, b, size);
        }
    }
    a = ((char *) data) + ++i * size;
    b = ((char *) data) + hi * size;
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

#define PARENT(i) ((i - 1) / 2)
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
        a = ((char *) data) + swap * size;
        b = ((char *) data) + child * size;
        if (cmp(a, b) < 0)
            swap = child;
        b = ((char *) data) + (child + 1) * size;
        if (child + 1 <= end && cmp(a, b) < 0)
            swap = child + 1;
        if (swap == root)
            break;
        a = ((char *) data) + root * size;
        b = ((char *) data) + swap * size;
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
    tmp = malloc(size);
    for (end = len - 1; end > 0; --end) {
        a = ((char *) data);
        b = ((char *) data) + end * size;
        VOIDSWAP(tmp, a, b, size);
        heapify(data, end, size, cmp);
    }
    free(tmp);
}

#undef PARENT
#undef LEFTCHILD
#undef RIGHTCHILD

int64_t binsearch(const void *data, size_t len, size_t size, cmpfunc cmp, const void *value) {
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

void binsert(void *data, size_t *len, size_t size, cmpfunc cmp, const void *value) {
    size_t index;
    void *src, *dst;
    index = find_index(data, *len, size, cmp, value);
    src = ((char *) data) + index * size;
    dst = ((char *) data) + (index + 1) * size;
    memmove(dst, src, ((*len)++ - index) * size);
}

void binserts(void *data, size_t *len, size_t size, cmpfunc cmp, const void *value) {
    int64_t index;
    void *src, *dst;
    index = find_index(data, *len, size, cmp, value);
    src = ((char *) data) + index * size;
    dst = ((char *) data) + (index + 1) * size;
    data = realloc(data, ((*len) + 1) * size);
    memmove(dst, src, ((*len)++ - index) * size);
}

void binremove(void *data, size_t *len, size_t size, cmpfunc cmp, const void *value) {
    int64_t index;
    void *src, *dst;
    index = binsearch(data, *len, size, cmp, value);  // Find element index.
    if (index == -1)
        return;
    src = ((char *) data) + (index + 1) * size;
    dst = ((char *) data) + index * size;
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

#undef CMPFUNC_INIT
