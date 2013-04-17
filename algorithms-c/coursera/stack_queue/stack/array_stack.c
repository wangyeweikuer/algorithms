#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "../arrays/arrays.h"
#include "stack.h"
#include "../errors.h"

void init_stack(stack * s)
{
	if (s->_array != NULL) {
		printf("Can't init twice!\n");
		exit(ERR_INIT_TWICE);
	}
	s->_array = (arrays *) malloc(sizeof(arrays));
	init(s->_array);
	s->_top_idx = 0;
}

void release_stack(stack * s)
{
	release(s->_array);	//先释放内部的
	free(s->_array);	//再释放其本身，谁申请，谁释放
	s->_top_idx = 0;
}

void push_stack(stack * s, int v)
{
	int ns = need_resize_before_add(s->_array);
	if (ns != -1) {
		resize(s->_array, ns, 0, s->_top_idx);
	}
	add_item(s->_array, s->_top_idx++, v);
}

int pop_stack(stack * s)
{
	int num = get_data_num(s->_array);
	if (num <= 0) {
		printf("not data ever\n");
		exit(ERR_NO_DATA);
	}
	int v = del_item(s->_array, --(s->_top_idx));
	int ns = need_resize_after_remove(s->_array);
	if (ns != -1) {
		resize(s->_array, ns, 0, s->_top_idx);
	}
	return v;
}

int get_stack_data_num(stack * s)
{
	return s->_top_idx;
}

int get_stack_size(stack * s)
{
	return s->_array->_size;
}
