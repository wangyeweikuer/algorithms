#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "arrays.h"
#include "../errors.h"

static int _init_size = 3;
// _increment_size 一定要比 _decrement_size 小，这样才不至于在大量增加和删除操作交替时，产生频繁的数组重分配
static int _increment_size = 2;
static int _decrement_size = 4;

static void check_param_not_nagetive(char *key, int num)
{
	if (num < 0) {
		printf("invalid %s:%d\n", key, num);
		exit(ERR_INVALID_PARAM);
	}
}

static void check_pointer_not_null(char *key, int *p)
{
	if (p == NULL) {
		printf("The pointer[%s] is null!\n", key);
		exit(ERR_OUT_OF_MEMORY);
	}
}

/*
 * @param min inclusive
 * @param max exclusive
 */
static void check_index_not_outofbounds(int idx, int min, int max)
{
	if (idx < min || idx >= max) {
		printf("Out of the bounds:[%d,%d)!\n", min, max);
		exit(ERR_OUT_OF_BOUNDS);
	}
}

int need_resize_before_add(arrays * a)
{
	if (a->_num == a->_size) {
		return a->_size * _increment_size;
	} else {
		return -1;
	}
}

int need_resize_after_remove(arrays * a)
{
	int newsize = a->_size / _decrement_size;
	if(newsize >= a->_num){
		newsize = newsize < _init_size ? _init_size : newsize;
		return newsize != a->_size ? newsize : -1;
	} else {
		return -1;
	}
}

void resize(arrays * a, int newsize, int cp_idx, int cp_length)
{
	check_param_not_nagetive("newsize", newsize);
	check_param_not_nagetive("cp_idx", cp_idx);
	check_param_not_nagetive("cp_length", cp_length);
	check_index_not_outofbounds(cp_idx, 0, a->_size);
	check_index_not_outofbounds(cp_length, 0, a->_num + 1);	//要加1

	int *tmp = (int *) malloc(sizeof(int) * newsize);
	check_pointer_not_null("tmp", tmp);

	int s = sizeof(int);
	if (a->_data != NULL && cp_length > 0) {
		if (cp_idx + cp_length > a->_size) {	//循环利用，需要复制两次
			memcpy(tmp, a->_data + cp_idx * s,
			       (a->_size - cp_idx) * s);
			memcpy(tmp, a->_data,
			       (cp_idx + cp_length - a->_size) * s);
		} else {
			memcpy(tmp, a->_data + cp_idx * s, cp_length * s);
		}
	}
	//必须要释放之前的指向的内容
	free(a->_data);		//NULL的指针可以free
	a->_data = tmp;
	a->_size = newsize;
}

void init(arrays * a)
{
	if (a->_data != NULL) {
		printf("Can't init twice!\n");
		exit(ERR_INIT_TWICE);
	}
	a->_data = (int *) malloc(sizeof(int) * _init_size);
	a->_size = _init_size;
	a->_num = 0;
}

void release(arrays * a)
{
	if (a->_data != NULL) {
		free(a->_data);
		a->_size = 0;
		a->_num = 0;
	}
}

void add_item(arrays * a, int idx, int v)
{
	check_index_not_outofbounds(idx, 0, a->_size);
	a->_data[idx] = v;
	a->_num++;
}

int del_item(arrays * a, int idx)
{
	if(a->_num == 0){
		printf("There is no any data to delete!\n");
		exit(ERR_NO_DATA);
	}
	check_index_not_outofbounds(idx, 0, a->_size);
	int v = a->_data[idx];
	a->_data[idx] = 0;	//清理数据
	a->_num--;
	return v;
}

int get_size(arrays * a)
{
	return a->_size;
}

int get_data_num(arrays * a)
{
	return a->_num;
}
