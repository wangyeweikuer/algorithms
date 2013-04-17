#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define LEN 10000
int nums[LEN];
int geneMedian(int start, int end)
{
	int mid = (start + end) / 2;
	int r = rand()%3;
	if(r==0){
		return mid;
	}else if(r == 1){
		return mid-1 < start ? start : mid-1;
	}else{
		return mid+1 >= end ? end-1 : mid+1;
	}
}
void swap(int x,int y){
	int v= nums[x];
	nums[x] = nums[y];
	nums[y] = v;
}
int partition(int start, int end)
{
	int mid = geneMedian(start, end);
	int v = nums[mid];
	int x = start;
	int y = end - 1;
	while (x < y) {
		while(x < mid && nums[x] <= v){
			x++;
		}
		while(y > mid && nums[y] >= v){
			y--;
		}
		if(x == mid){
			nums[mid] = nums[y];
			mid = y;
		}else if(y == mid){
			nums[mid] = nums[x];
			mid = x;
		}else{
			swap(x,y);
		}
	}
	nums[mid] = v;
	return mid;
}


void quick_sort(int start, int end)
{
	if (start >= end - 1) {
		return;
	}
	int mid = partition(start, end);
	quick_sort(start, mid);
	quick_sort(mid + 1, end);
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
	while (i < 20 && i < n) {
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
		quick_sort(0, n);
		printTop(n, 0);
	}
	return 0;
}
