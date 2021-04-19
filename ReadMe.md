### Intro
Implementation for basic datastructure and algorithm
### Sort.cpp

#### Quick Sort

Time Complexity O(nlog(n))-Bestcase | O(n^2), Space: no need for extra space when swap is used
1. partition by pivot (choose the last element) (elements are sorted)
2. quicksort(left_part)
3. quicksort(right_part)

#### Merge Sort
Time Complexity O(nlog(n)), Space O(n)
1. divide array into two halves
2. mergesort(left_part)
3. mergesort(right_part)
4. merge(left_part, right_part) (elements are sorted)

### linked_list
1. sll.c single linked list
2. dll.c double linked list