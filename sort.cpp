#include <iostream>
#include <algorithm>
#include <ctime>
#include <memory>
using namespace std;

enum SortType
{
    QUICK_SORT = 0,
    MERGE_SORT
};

template <typename Iter>
void print(Iter begin, Iter end)
{
    for (; begin != end; begin++)
    {
        cout << (*begin) << " ";
    }
    cout << endl;
}

template <typename Iter>
void fill(Iter begin, Iter end)
{
    int N = (end - begin);
    for (; begin != end; begin++)
    {
        *begin = (rand() % N);
    }
}

template <typename T>
void swap(T *a, T *b)
{
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template <typename Iter>
void quicksort(Iter l, Iter r)
{
    if (l < r)
    {
        // partition
        auto pivot = *(r - 1);
        Iter ptr = l;
        Iter l_begin = l;
        for (; ptr < r; ptr++)
        {
            if (*ptr < pivot)
            {
                swap(ptr, l_begin);
                l_begin++;
            }
        }
        Iter mid = l_begin;
        swap(l_begin, r - 1);

        quicksort(l, mid);
        quicksort(mid + 1, r);
    }
}

void print_l(int levels, const char *msg)
{
    for (int i = 0; i < levels; i++)
        cout << " ";
    cout << msg << ": ";
}

template <typename Iter>
void mergesort(Iter l, Iter r, int levels)
{
    int N = (r - l);
    if (N <= 1)
        return;

    Iter mid = l + (N / 2);
    // print_l(levels, "-->left");
    // print(l, mid);
    mergesort(l, mid, levels + 1);
    // print_l(levels, "-->right");
    // print(mid, r);
    mergesort(mid, r, levels + 1);

    //merge
    int *a = new int[N];
    Iter l_begin = l;
    Iter r_begin = mid;
    int i = 0;
    while (l_begin < mid && r_begin < r)
    {
        if (*l_begin < *r_begin)
        {
            a[i] = *l_begin;
            l_begin++;
        }
        else
        {
            a[i] = *r_begin;
            r_begin++;
        }
        i++;
    }

    for (; l_begin < mid; l_begin++)
    {
        a[i] = *l_begin;
        i++;
    }

    for (; r_begin < r; r_begin++)
    {
        a[i] = *r_begin;
        i++;
    }

    i = 0;
    Iter ptr = l;
    for (; i < N; i++)
    {
        *(ptr + i) = a[i];
    }
    // print_l(levels, "--merged");
    // print(l, r);
    delete[] a;
}

template <typename Iter>
void sort(Iter begin, Iter end, SortType type)
{
    if (type == QUICK_SORT)
    {
        quicksort(begin, end);
    }
    else if (type == MERGE_SORT)
    {
        mergesort(begin, end, 0);
    }
}

template <typename T>
bool check(T arr[], int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

int main()
{
    const int N = 100000000;
    int *arr = new int[N];

    fill(arr, arr + N);
    // print(arr, arr + N);

    clock_t start = clock();
    sort(arr, arr + N, QUICK_SORT);
    // sort(arr, arr + N, MERGE_SORT);
    //std::sort(arr, arr + N);
    cout << "Time takes " << (double)(clock() - start) / (CLOCKS_PER_SEC) << " ms" << endl;
    cout << "After sort" << endl;
    // print(arr, arr + N);
    if (check(arr, N) == false)
    {
        cout << "Wrong answer" << endl;
    }
    delete[] arr;
    return 0;
}