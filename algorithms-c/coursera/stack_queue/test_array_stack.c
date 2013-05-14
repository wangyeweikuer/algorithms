#include <stdio.h>
#include <stdlib.h>
#include "stack/stack.h"
int main()
{
	int n;
	stack tmp = { 0, 0 };
	stack *s = &tmp;
	init_stack(s);
	printf("input int:");
	while (scanf("%d", &n) != EOF) {
		if (n < 0) {
			int v = pop_stack(s);
			printf("pop() -> v:%d,num:%d,size:%d\n", v,
			       get_stack_datanum(s), get_stack_size(s));
		} else if (n > 0) {
			push_stack(s, n);
			printf("push() -> num:%d,size:%d\n",
			       get_stack_datanum(s), get_stack_size(s));
		} else {
			break;
		}
		printf("input int:");
	}
	printf("over...\n");
	release_stack(s);	//释放内存
	return 0;
}
