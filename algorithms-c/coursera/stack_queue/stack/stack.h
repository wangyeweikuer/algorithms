#ifndef _stack_h_
#define _stack_h_

#include "../arrays/arrays.h"

typedef struct {
	arrays *_array;
	int _top_idx;
} stack;
/*
 * 初始化操作
 */
void init_stack(stack * s);

/*
 * 释放
 */
void release_stack(stack * s);

void push_stack(stack * s, int v);

int pop_stack(stack * s);

/**
 * 堆栈中的数据量
 */
int get_stack_data_num(stack * s);

/*
 * 堆栈大小
 */
int get_stack_size(stack * s);

#endif
