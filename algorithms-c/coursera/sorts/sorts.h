#ifndef __sort_h_
#define __sort_h_
#include <stdio.h>

void insertion_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *));

void selection_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *));

void bubble_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *));

void shell_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *));

void merge_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *));

void merge_sort_optimal(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *));

void merge_sort_bottomup(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *));

void quick_sort_naive(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *));

void quick_sort_naive2(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *));

void quick_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *));

void heap_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *));

#endif
