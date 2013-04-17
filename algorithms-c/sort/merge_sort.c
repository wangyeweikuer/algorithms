#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define LEN 10000
int nums[LEN];
int bak[LEN];
void merge(int start, int mid, int end)
{
	int i = start;
	int j = mid;
	int v = start;
	while (i < mid && j < end) {
		if (nums[i] <= nums[j]) {
			bak[v++] = nums[i++];
		} else {
			bak[v++] = nums[j++];
		}
	}
	while (i < mid) {
		bak[v++] = nums[i++];
	}
	while (j < end) {
		bak[v++] = nums[j++];
	}
	for (i = start; i < end; i++) {
		nums[i] = bak[i];
	}
}

void merge_sort(int start, int end)
{
	if (start >= end - 1) {
		return;
	}
	int mid = (start + end) / 2;
	merge_sort(start, mid);
	merge_sort(mid, end);
	merge(start, mid, end);
}

void myrand(int len)
{
	srand(time(NULL));
	int i = 0;
	while (i < len) {
		int n = rand() % LEN / 13;
		nums[i++] = n;
	}
}

void printTop(int n, int beforeSort)
{
	printf("%s sort top %d nums:\n", (beforeSort == 1 ? "Before" : "After"), n);
	int i = 0;
	while (i < 10 && i < n) {
		if (i > 0) {
			printf("\t");
		}
		printf("%d", nums[i++]);
	}
	printf("\n ------- \n");
}

int main(void)
{
	int n;
	while (1) {
		printf("please input size:", &n);
		scanf("%d", &n);
		if (n >= LEN || n <= 0) {
			printf("size(%d) is not valid!", n);
			continue;
		}
		myrand(n);
		printTop(n, 1);
		merge_sort(0, n);
		printTop(n, 0);
	}
	return 0;
}
