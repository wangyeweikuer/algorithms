#include <stdio.h>
#include <stdlib.h>
#include "queue/queue.h"

int main()
{
	int n;
	queue tmp = { 0, 0, 0 };
	queue *s = &tmp;
	init_queue(s);
	printf("input int:");
	while (scanf("%d", &n) != EOF) {
		if (n < 0) {
			int v = de_queue(s);
			printf("pop() -> v:%d,num:%d,size:%d\n", v,
			       get_queue_datanum(s), get_queue_size(s));
		} else if (n > 0) {
			en_queue(s, n);
			printf("push() -> num:%d,size:%d\n",
			       get_queue_datanum(s), get_queue_size(s));
		} else {
			break;
		}
		printf("input int:");
	}
	printf("over...\n");
	release_queue(s);	//释放内存
	return 0;
}
