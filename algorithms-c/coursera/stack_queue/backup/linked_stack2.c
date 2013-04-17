#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/** 数组元素 */
typedef struct node {
	struct node *next;
	int value;
};
typedef struct linked_stack {
	struct node *head;
	struct node *last;	//快速定位到最后一个元素
	int num;
	int initialized;
} stack;

int *_resize(int *data, int newsize, int copynum)
{
	int *tmp = (int *) malloc(newsize * sizeof(int));
	if (tmp == 0) {
		printf("Error allocating memory!\n");
		exit(1);
	}
	tmp = (int *) memcpy(tmp, data, sizeof(int) * copynum);
	free(data);		//释放空间
	return tmp;
}

void init_stack()
{
	if (stack->initialized != 0) {
		printf("Error to init twice !\n");
		exit(1);
	}
	stack->head = 0;
	stack->last = 0;
	stack->num = 0;
	stack->initialized = 1;
}

void push_stack(int v)
{
	struct node tmp = { 0, v };
	if (stack->head == 0) {
		stack->head = tmp;
		stack->last = tmp;
	} else {
		stack->last->next = tmp;
		stack->last = tmp;
	}
	stack->num++;
}

int pop_stack(int *v)
{
	if (num == 0) {		//或者判断指针是否为空
		return 0;
	}
	(*v) = stack->last->value;
	stack->last data[num] = 0;	//清楚数据引用（在某些虚拟机语言，如java，需要帮助虚拟机解除对象关系，从而在GC时可以释放对象）
	int newsize = size / decrement_factor;
	if (newsize >= num) {	//如果数据量足够小，则需要减少空间
		newsize = (newsize <= init_size ? init_size : newsize);	//空间再小也不能少于初始化值
		if (newsize != size) {	//防止没有必要的重分配
			data = _resize(data, (size = newsize), num);
		}
	}
	return 1;
}

int get_data_num()
{
	return num;
}

int get_stack_size()
{
	return get_data_num();
}
