#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define LEN 100001

int read_ints(int *all, char *file)
{
	int len = 0;
	FILE *f = fopen(file,"r");
	if(f == NULL){
		printf("The file[%s] isn't existing\n",file);
		exit(1);
	}
	while (fscanf(f,"%d", &all[len]) != EOF) {
		len++;
	}
	fclose(f);
	return len;
}

long merge_cal_inversions(int *all, int *help, int start, int mid, int end)
{
	memcpy(help + start, all + start, (end - start + 1) * sizeof(int));
	int i = start, j = mid + 1, k = start;
	long num = 0;
	while (k <= end) {
		if (i > mid) {
			all[k++] = help[j++];
		} else if (j > end) {
			all[k++] = help[i++];
			num += end - mid;
		} else if (help[i] < help[j]) {
			all[k++] = help[i++];
			num += j - mid - 1;
		} else {
			all[k++] = help[j++];
		}
	}
	return num;
}

long merge_sort_cal_inversions(int *all, int *help, int start, int end)
{
	if (start >= end) {
		return 0;
	}
	int mid = (start + end) >> 1;
	long a = merge_sort_cal_inversions(all, help, start, mid);
	long b = merge_sort_cal_inversions(all, help, mid + 1, end);
	return a + b + merge_cal_inversions(all, help, start, mid, end);
}

static void swap(int *all,int a,int b)
{
	if(a == b){
		return;
	}
	int tmp = all[a];
	all[a] = all[b];
	all[b] = tmp;
}

static int _partition_first(int *all,int start,int end)
{
	int i = start,j = start+1,pivot = start;
	while(j<=end){
		if(all[pivot] > all[j]){
			swap(all,++i,j);
		}
		j++;
	}
	swap(all,i,pivot);
	return i;
}

static int _partition_mid(int *all,int start,int end)
{
	int mid = (end + start) / 2;
	if(all[mid] < all[start] && all[mid] > all[end] ||
		all[mid] > all[start] && all[mid] < all[end]){
		swap(all,start,mid);
	}else if(all[end] < all[start] && all[end] > all[mid] ||
		all[end] > all[start] && all[end] < all[mid]){
		swap(all,start,end);
	}
	return _partition_first(all,start,end);
}

static int _partition_end(int *all,int start,int end)
{
	swap(all,start,end);
	return _partition_first(all,start,end);
}

long quick_sort(int *all,int start,int end,int (*partition)(int *,int ,int ))
{
	if(start >= end){
		return 0;
	}
	int mid = partition(all,start,end);
	long a1 = quick_sort(all,start,mid-1,partition);
	long a2 = quick_sort(all,mid+1,end,partition);
	return a1 + a2 + end - start;
}

int* copy_ints(int num,int *all)
{
	int *new = (int *) malloc(sizeof(int) * num);
	memcpy(new,all,num*sizeof(int));
	return new;
}

int main(int len, char *args[])
{
	if (len <= 1) {
		printf("No input file\n");
		exit(1);
	}
	int *all = (int *) malloc(sizeof(int) * LEN);
	int num = read_ints(all, args[1]);
	int *all1 = copy_ints(num,all);
	int *all2 = copy_ints(num,all);
	long l1 = quick_sort(all,0,num-1,_partition_first);
	long l2 = quick_sort(all1,0,num-1,_partition_mid);
	long l3 = quick_sort(all2,0,num-1,_partition_end);
	printf("%ld,%ld,%ld\n",l1,l2,l3);
//	int *help = (int *) malloc(sizeof(int) * LEN);
//	long res = merge_sort_cal_inversions(all, help, 0, num-1);
//	printf("result : %ld\n", res);
	free(all);
	free(all1);
	free(all2);
}

