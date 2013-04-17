#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/** 数组元素 */
int *data;
int size;
int num;
int init_size = 3;
int decrement_factor = 4;
int increment_factor = 2;

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
	if (data != 0) {
		printf("Error to init twice !\n");
		exit(1);
	}
	data = _resize(data, (size = init_size), (num = 0));
}

void release_stack()
{
	free(data);
}

void push_stack(int v)
{
	if (num == size) {
		data = _resize(data, (size *= increment_factor), num);
	}
	data[num++] = v;
}

int pop_stack(int *v)
{
	if (num == 0) {
		return 0;
	}
	(*v) = data[--num];
	data[num] = 0;		//清楚数据引用（在某些虚拟机语言，如java，需要帮助虚拟机解除对象关系，从而在GC时可以释放对象）
	int newsize = size / decrement_factor;
	if (newsize >= num) {	//如果数据量足够小，则需要减少空间
		newsize = (newsize <= init_size ? init_size : newsize);	//空间再小也不能少于初始化值
		if (newsize != size) {	//防止没有必要的重分配
			data = _resize(data, (size = newsize), num);
		}
	}
	return 1;
}

int get_stack_size()
{
	return size;
}

int get_data_num()
{
	return num;
}
