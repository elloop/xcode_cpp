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
void print_heap_tree(elem_t *heap, size_t n)
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
    for (int i=n/2 - 1; i>=0; --i)
    {
        ensure_heap(heap, i, n);
    }
}

void heap_sort(elem_t *heap, size_t n)
{
    make_heap(heap, n);
    size_t last = n - 1;

    while (last > 0) 
    {
        std::swap(heap[0], heap[last]);
        make_heap(heap, last);
        --last;
    }
}


BEGIN_TEST(HeapTest, MakeHeap, @@);

elem_t heap[N] = {49, 38, 65, 97, 76, 13, 27, 49};

print_array(heap);

print_heap_tree(heap, N); cr;

pcln("ajust");

make_heap(heap, N);

print_heap_tree(heap, N); cr;

pcln("begin of heap sort");
pcln("begin of heap sort");
pcln("begin of heap sort");
heap_sort(heap, N);
pcln("end of heap sort");
pcln("end of heap sort");
pcln("end of heap sort");

print_array_reverse(heap);

END_TEST;

// ========================= use stl heap ==========================
BEGIN_TEST(HeapTest, stlheap, @@);

int myints[] = {9, 38, 65, 97, 76, 13, 27, 49};
int len = ARRAY_LEN(myints);
std::vector<int> v(myints,myints+len);

std::make_heap (v.begin(),v.end());
std::cout << "initial max heap   : " << v.front() << '\n';

//std::pop_heap (v.begin(),v.end());
//v.pop_back();
//printContainer(v);
//std::cout << "max heap after pop : " << v.front() << '\n';

v.push_back(99);
//std::push_heap (v.begin(),v.end());
std::make_heap(v.begin(), v.end());
std::cout << "max heap after push: " << v.front() << '\n';

std::sort_heap (v.begin(),v.end());

pln("final sorted range :");
for (unsigned i=0; i<v.size(); i++)
{
    p(" "); p(v[i]);
}


END_TEST;

NS_END(heap);
NS_END(elloop);


