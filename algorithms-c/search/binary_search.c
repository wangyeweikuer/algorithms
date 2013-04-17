#include <stdio.h>
//int a[] = { 1, 3, 4, 7, 8, 12, 15, 16, 17, 20, 25, 27, 29, 30 };
int a[] = {1};
/**
 * 按照数组的[a,b]方式来查找
 */
int binary_search(int v, int len)
{
	int low = 0;
	int hig = len - 1;
	while (low <= hig) {//必须相等，否则遗漏
		int mid = (low + hig + 1) >> 1; //需要+1
		if (a[mid] > v) {
			hig = mid - 1;
		} else if (a[mid] < v) {
			low = mid + 1;
		}else{
			return mid;
		}
	}
	return -1;
}
/**
 * 按照数组的[a,b)方式来查找
 */
int binary_search2(int v,int len){
	int low = 0;
	int hig = len;
	while(low < hig){ //不能相等，否则越界
		int mid = (low+hig)>>1; //不能+1
		if (a[mid] > v) {
			hig = mid - 1;
		} else if (a[mid] < v) {
			low = mid + 1;
		}else{
			return mid;
		}
	}
	return -1;
}
int main(void)
{
	int n;
	while (scanf("%d", &n) != -1) {
		int idx = binary_search(n, sizeof(a) / 4);
		printf("binary_search value(%d),found index:%d\n", n, idx);
		int idx2 = binary_search2(n, sizeof(a) / 4);
		printf("binary_search2 value(%d),found index:%d\n", n, idx2);
	}
}
