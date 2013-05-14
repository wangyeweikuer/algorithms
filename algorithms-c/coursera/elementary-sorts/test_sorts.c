#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <math.h>
//#include "sorts.h"

int int_cmp(void *a, void *b)
{
	return *((int *) a) - *((int *) b);
}

int int_cmp_reverse(void *a, void *b)
{
	return -int_cmp(a, b);
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

int *rand_items(int len)
{
	srand(time(NULL));
	int *rs = (int *) malloc(sizeof(int) * len);
	int i = 0;
	while (i < len) {
		*(rs + i++) = abs(rand() % 200);
	}
	return rs;
}

void print_items(int len, int *items)
{
	int i = 0;
	while (i < len) {
		printf("%d ", items[i++]);
	}
	printf("\n");
}

void call_fn(int len,
	     void (*fn) (void *, int, int, size_t,
			 int (*cmp) (void *, void *)), size_t type_size,
	     int (*cmp) (void *, void *), char *fn_name)
{
	printf("sort function:%s\nbefore sort:\n", fn_name);
	int *rs = rand_items(len);
	print_items(len, rs);
	fn(rs, 0, len - 1, type_size, cmp);
	printf("after sort:\n");
	print_items(len, rs);
	printf("-----------\n");
	free(rs);
}

int char_cmp(void *a, void *b)
{
	char c1 = *((char *) a);
	char c2 = *((char *) b);
	return (int) (c1 - c2);
}

int double_cmp(void *a, void *b)
{
	double d1 = *((double *) a);
	double d2 = *((double *) b);
	return d1 > d2 ? -1 : (d1 < d2 ? 1 : 0);
}

int main()
{
//      int a[] = { 2, 3, 4, 1 };
//      int len = 4;
//      print_items(len, a);
//      insertion_sort(a, 0, len - 1, sizeof(int), int_cmp);
//      print_items(len, a);
//
//      int b[] = { 2, 3, 4, 1 };
//      len = 4;
//      print_items(len, b);
//      insertion_sort(b, 0, len - 1, sizeof(int), int_cmp_reverse);
//      print_items(len, b);
//      int len = 10;
//      call_fn(len, insertion_sort, sizeof(int), int_cmp,
//              "insertion_sort");
//      call_fn(len, insertion_sort, sizeof(int), int_cmp_reverse,
//              "insertion_sort");
//    call_fn(len, selection_sort, "selection_sort");
//    call_fn(len, bubble_sort, "bubble_sort");
//      char cs[] = { 'U', 'b', 'K', 'j', 'r', 'a', 'x', 'Y', 'h', 'H' };
//      insertion_sort(cs, 0, 9, sizeof(char), char_cmp);
//      for (int i = 0; i < 10; i++) {
//              printf("%c ", cs[i]);
//      }
//      printf("\n");

	double ds[] =
	    { 9.875, 9.857, 2.3345, 5, 32, 6.232, 10, -1, 111, 8 };
	for (int i = 0; i < 10; i++) {
		printf("%lf ", ds[i]);
	}
	printf("\n");
	insertion_sort(ds, 0, 9, sizeof(double), double_cmp);
	for (int i = 0; i < 10; i++) {
		printf("%lf ", ds[i]);
	}
	printf("\n");
}
