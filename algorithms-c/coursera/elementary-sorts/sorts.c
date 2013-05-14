#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "sorts.h"

int less(void *a, void *b)
{
	return *((int *) a) < *((int *) b);
}

int less_equal(void *a, void *b)
{
	return *((int *) a) <= *((int *) b);
}

void swap(void *a, void *b, size_t type_size)
{
	for (int i = 0; i < type_size; i++) {
		char tmp = *((char *) (a + i));
		*((char *) (a + i)) = *((char *) (b + i));
		*((char *) (b + i)) = tmp;
	}
}

void insertion_sort(void *a, int start, int end, size_t type_size,
		    int (*cmp) (void *, void *))
{
	int i, j;
	for (i = start + 1; i <= end; i++) {
		for (j = i - 1; j >= start; j--) {
			void *p1 = a + (j + 1) * type_size;
			void *p2 = a + j * type_size;
			int c = cmp(p1, p2);
			if (c < 0) {
				swap(p1, p2, type_size);
			} else {
				break;
			}
		}
	}
}

void selection_sort(void *a, int start, int end, size_t type_size,
		    int (*cmp) (void *, void *))
{
	int i, j;
	for (i = start; i < end; i++) {
		for (j = i + 1; j <= end; j++) {
			if (less(a + j, a + i)) {
				swap(a + j, a + i);
			}
		}
	}
}

void bubble_sort(void *a, int start, int end, size_t type_size,
		 int (*cmp) (void *, void *))
{
	int i, j;
	for (i = end; i > start; i--) {
		for (j = i; j > start; j--) {
			if (less(a + j, a + j - 1)) {
				swap(a + j, a + j - 1);
			}
		}
	}
}

void shell_sort(void *a, int start, int end, size_t type_size,
		int (*cmp) (void *, void *))
{

}

void merge_sort(void *a, int start, int end, size_t type_size,
		int (*cmp) (void *, void *))
{

}

void quick_sort(void *a, int start, int end, size_t type_size,
		int (*cmp) (void *, void *))
{
}

void heap_sort(void *a, int start, int end, size_t type_size,
	       int (*cmp) (void *, void *))
{
}
