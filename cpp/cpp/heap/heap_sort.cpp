#include "inc.h"

NS_BEGIN(elloop);
NS_BEGIN(heap);

static const int N = 8;

typedef int elem_t;
elem_t elem_t_default = 0;

void print_spaces(size_t count)
{
    for (size_t i=0; i<count; ++i) 
    {
        p(" ");
    }
}

// print heap as a binary tree.
void print_heap(elem_t *heap, size_t n)
{
    const int CONSOLE_WIDTH = 96;

    size_t gap = CONSOLE_WIDTH / 2;
    size_t pow2 = 1;
    size_t i = 0;
    while (i < n) 
    {
        print_spaces(gap);
        for (size_t j=0; j<pow2 && i < n; ++j) 
        {
            p(heap[i++]);
            print_spaces(2 * gap);
        }
        cr;
        pow2 *= 2;
        gap /= 2;
    }
}

void ensure_heap(elem_t *heap, size_t root, size_t n)
{
    size_t smaller_index = root;
    size_t left_child = 2 * (root + 1) - 1;
    size_t right_child = 2 * (root + 1);

    while (left_child < n ) 
    {
        if (heap[root] > heap[left_child]) 
        { 
            smaller_index = left_child;
        }

        if (right_child < n && (heap[smaller_index] > heap[right_child])) 
        {
            smaller_index = right_child;
        }

        std::swap(heap[root], heap[smaller_index]);

        if (smaller_index == root) 
        {
            return;
        }     
        root = smaller_index;
        left_child = 2 * (root + 1) - 1;
        right_child = 2 * (root + 1);
    }
}

void make_heap(elem_t *heap, size_t n)
{
    // 1. array[n]
    // 2. adjust from n/2-1 to 0.
    //
    for (int i=n/2 - 1; i>=0; --i) 
    {
        LOGD("make heap at position: %d, elem: %d\n", n/2, heap[i]);
        ensure_heap(heap, i, n);
        print_heap(heap, n);
    }
}


void print_heap_array(elem_t *heap, size_t n)
{
    for (size_t i=0; i<n; ++i) 
    {
        p(heap[i]); p(" ");
    }
}

RUN_GTEST(HeapTest, MakeHeap, @@);

elem_t heap[N] = {49, 38, 65, 97, 76, 13, 27, 49};

print_heap_array(heap, N); cr;

print_heap(heap, N); cr;

pcln("ajust");

make_heap(heap, N);

print_heap(heap, N); cr;

END_TEST;


NS_END(heap);
NS_END(elloop);


