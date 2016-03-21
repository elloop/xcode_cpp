#include "inc.h"

NS_BEGIN(elloop);
NS_BEGIN(sort_algorithm);

size_t partition(int *a, size_t low, size_t high)
{
    int v = a[low];
    while (low < high) 
    {
        while (low < high && a[high] >= v) 
            --high;
        a[low] = a[high];
        while (low < high && a[low] <= v)
            ++low;
        a[high] = a[low];
    }
    a[low] = v;
    return low;
}

void quick_sort(int *a, size_t low, size_t high)
{
    if (low < high) 
    {
        size_t div = partition(a, low, high);
        quick_sort(a, low, div - 1);
        quick_sort(a, div + 1, high);
    }
}


RUN_GTEST(SortAlgorithm, QuickSort, @@);

int a[] = {9, 1, 2, 10, 34, 3, 5, 20};

print_array(a);

quick_sort(a, 0, ARRAY_LEN(a) - 1);

print_array(a);

END_TEST;

NS_END(sort_algorithm);
NS_END(elloop);
