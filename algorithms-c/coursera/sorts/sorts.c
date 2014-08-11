#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "sorts.h"
#define MERGE_SORT_MIN_SIZE 7	//小于这个值的，都用插入排序解决问题
/**
 * 1、不知道void指向的数据类型的长度，所以必须要带type_size；
 * 2、void* 对应的元素无法交换，而char长度为1字节,且为最小长度，所以用它来作为移动值的媒介
 */
static void swap(void *a, int l_idx, int r_idx, size_t type_size)
{
	if (l_idx == r_idx) {
		return;
	}
	void *p1 = a + l_idx * type_size;
	void *p2 = a + r_idx * type_size;
	for (int i = 0; i < type_size; i++) {
		char tmp = *((char *) (p1 + i));
		*((char *) (p1 + i)) = *((char *) (p2 + i));
		*((char *) (p2 + i)) = tmp;
	}
}

/**
 * @param a 原始数组
 * @param idx 某种元素对应的数组下标
 * @param type_size 数组中元素的字节宽度
 */
static void *_get_index_of(void *a, int idx, size_t type_size)
{
	return a + idx * type_size;
}

static int do_cmp(void *a, int l_idx, int r_idx, size_t type_size, int (*cmp) (void *, void *))
{
	return cmp(_get_index_of(a, l_idx, type_size), _get_index_of(a, r_idx, type_size));
}

static void _copy_item(void *dest, int didx, void *src, int sidx, size_t type_size)
{
	void *a = _get_index_of(dest, didx, type_size);
	void *b = _get_index_of(src, sidx, type_size);
	memcpy(a, b, type_size);
}

void insertion_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	int i, j;
	for (i = start + 1; i <= end; i++) {
		for (j = i; j > start; j--) {
			int c = do_cmp(a, j, j - 1, type_size, cmp);
			if (c < 0) {
				swap(a, j, j - 1, type_size);
			} else {
				break;
			}
		}
	}
}

void selection_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	int i, j;
	for (i = start; i < end; i++) {
		for (j = i + 1; j <= end; j++) {
			int c = do_cmp(a, j, i, type_size, cmp);
			if (c < 0) {
				swap(a, j, i, type_size);
			}
		}
	}
}

void bubble_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	int i, j;
	for (i = start; i < end; i++) {
		for (j = end; j > i; j--) {
			int c = do_cmp(a, j, j - 1, type_size, cmp);
			if (c < 0) {
				swap(a, j, j - 1, type_size);
			}
		}
	}
}

void shell_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	int gaps[] = { 23, 13, 7, 4, 2, 1 };
	int gn = sizeof(gaps) / sizeof(int);
	int g, i, j;
	for (g = 0; g < gn; g++) {
		for (i = start + gaps[g]; i <= end; i++) {
			for (j = i; j - gaps[g] >= start; j -= gaps[g]) {
				int c = do_cmp(a, j, j - gaps[g], type_size, cmp);
				if (c < 0) {
					swap(a, j, j - gaps[g], type_size);
				} else {
					break;
				}
			}
		}
	}
}

static void _merge_internal(void *a, void *help, int start, int mid,
			    int end, size_t type_size, int (*cmp) (void *, void *))
{
	memcpy(help, a + (start * type_size), (end - start + 1) * type_size);	//move all to help array
	int i = start, j = start, k = mid + 1;
	while (i <= end) {
		if (j > mid)
			_copy_item(a, i++, help, (k++) - start, type_size);
		else if (k > end)
			_copy_item(a, i++, help, (j++) - start, type_size);
		else if (do_cmp(help, j - start, k - start, type_size, cmp) <= 0)
			_copy_item(a, i++, help, (j++) - start, type_size);
		else
			_copy_item(a, i++, help, (k++) - start, type_size);
	}
}

static void _merge_sort(void *a, void *help, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	if (start >= end) {
		return;
	}
	int mid = (end + start) / 2;
	_merge_sort(a, help, start, mid, type_size, cmp);
	_merge_sort(a, help, mid + 1, end, type_size, cmp);
	_merge_internal(a, help, start, mid, end, type_size, cmp);
}

void merge_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	void *help = (void *) malloc((end - start + 1) * type_size);
	_merge_sort(a, help, start, end, type_size, cmp);
}

static void _merge_sort_optimal(void *a, void *help, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	if (end - start + 1 <= MERGE_SORT_MIN_SIZE) {	//如果数组长度很小，就不用递归，转而选择插入排序，会更快
		insertion_sort(a, start, end, type_size, cmp);
	} else {
		int mid = (end + start) / 2;
		_merge_sort_optimal(a, help, start, mid, type_size, cmp);
		_merge_sort_optimal(a, help, mid + 1, end, type_size, cmp);
		if (do_cmp(a, mid, mid + 1, type_size, cmp) > 0) {	//如果排序好的左右半段，左侧的最后一个元素小于等于右侧第一个元素，那么整体已经有序
			_merge_internal(a, help, start, mid, end, type_size, cmp);
		}
	}
}

void merge_sort_optimal(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	void *help = (void *) malloc((end - start + 1) * type_size);
	_merge_sort_optimal(a, help, start, end, type_size, cmp);
}

void merge_sort_bottomup(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	int step, j;
	void *help = (void *) malloc((end - start + 1) * type_size);
	for (step = 1; step < (end - start + 1); step <<= 1) {
		for (j = start; j <= end; j += step * 2) {
			int mid = j + step - 1;
			if (mid < end) {
				int e = j + step * 2 - 1;
				e = e > end ? end : e;
				if (do_cmp(a, mid, mid + 1, type_size, cmp) > 0) {
					_merge_internal(a, help, j, mid, e, type_size, cmp);
				}
			}
		}
	}
}

/**
 *从两头扫描的方式，i表示小于pivot的边界，j表示大于pivot的边界
 *
 */
static int _partition(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	int i = start, j = end + 1;
	int pivot = start;
	while (1) {
		while (do_cmp(a, ++i, pivot, type_size, cmp) <= 0 && i < end);
		while (do_cmp(a, --j, pivot, type_size, cmp) >= 0 && j > start);	//j > start + 1 有问题
		if (i >= j) {
			break;
		}
		swap(a, i, j, type_size);
	}
	swap(a, start, j, type_size);	//j的位置所对应的值，肯定比start位置的值小；
	return j;
}

void quick_sort_naive(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	if (start >= end) {
		return;
	}
	int mid = _partition(a, start, end, type_size, cmp);
	quick_sort_naive(a, start, mid - 1, type_size, cmp);
	quick_sort_naive(a, mid + 1, end, type_size, cmp);
}

/**
 * 算法课中的另一种分区方式,从前往后扫描模式,i表示小于pivot的边界，j表示大于pivot的边界
 */
static int _partition2(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	int i = start, j = start + 1, pivot = start;
	while (j <= end) {
		if (do_cmp(a, pivot, j, type_size, cmp) > 0) {
			swap(a, ++i, j, type_size);
		}
		j++;
	}
	swap(a, pivot, i, type_size);	//将pivot居中
	return i;
}

void quick_sort_naive2(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
	if (start >= end) {
		return;
	}
	int mid = _partition2(a, start, end, type_size, cmp);
	quick_sort_naive2(a, start, mid - 1, type_size, cmp);
	quick_sort_naive2(a, mid + 1, end, type_size, cmp);
}

void quick_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
}

void heap_sort(void *a, int start, int end, size_t type_size, int (*cmp) (void *, void *))
{
}
