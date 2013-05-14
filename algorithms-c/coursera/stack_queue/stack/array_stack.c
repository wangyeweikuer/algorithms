#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "../array/array.h"
#include "stack.h"
#include "../errors.h"

void init_stack(stack * s)
{
	if (s->_array != NULL) {
		printf("Can't init twice for stack!\n");
		exit(ERR_INIT_TWICE);
	}
	s->_array = new_array();
	if(s->_array->_data != NULL){
		printf("haha\n");
	}
	init_array(s->_array);
	s->_top_idx = 0;
}

void release_stack(stack * s)
{
	release_array(s->_array);	//先释放内部的
	free(s->_array);	//再释放其本身，谁申请，谁释放
	s->_array = NULL;
	s->_top_idx = 0;
}

void push_stack(stack * s, int v)
{
	int ns = need_resize_before_add(s->_array);
	if (ns != -1) {
		resize_array(s->_array, ns, 0, s->_top_idx);
	}
	add_array_item(s->_array, s->_top_idx++, v);
}

static void check_data_avaliable(int num)
{
	if (num <= 0) {
		printf("not data ever\n");
		exit(ERR_NO_DATA);
	}
}

int pop_stack(stack * s)
{
	check_data_avaliable(get_array_datanum(s->_array));
	int v = del_array_item(s->_array, --(s->_top_idx));
	int ns = need_resize_after_remove(s->_array);
	if (ns != -1) {
		resize_array(s->_array, ns, 0, s->_top_idx);
	}
	return v;
}

int get_stack_top(stack * s)
{
	check_data_avaliable(get_array_datanum(s->_array));
	return get_array_item(s->_array,s->_top_idx-1);
}

int get_stack_datanum(stack * s)
{
	return s->_top_idx;
}

int get_stack_size(stack * s)
{
	return s->_array->_size;
}

