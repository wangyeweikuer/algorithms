#ifndef _array_h_
#define _array_h_

#include <stddef.h>

/*
 * 完成通用的数组内存管理代码；
 * 内部函数和内部成员变量，都用static限定，内部变量前加_做区别
 */
typedef struct {
	int *_data;		//数据数组
	int _size;		//数组长度
	int _num;		//有效数据的数量
} array;

/**
 * 判断在增加前是否需要重新调整数组
 * @return 返回-1表示不需要，返回大于0的值表示需要重新分配的大小
 */
int need_resize_before_add(array * a);

/**
 * 判断在移除之后是否需要重新调整数组
 * @return 返回-1表示不需要，返回大于0的值表示需要重新分配的大小
 */
int need_resize_after_remove(array * a);

/*
 * 调整数组大小，重新分配;自动处理原来数组有循环使用的情况；新的数据从0开始分配
 */
void resize_array(array * a, int newsize, int cp_idx, int cp_length);

/**
 * 初始化一个对象
 */
array * new_array();

/**
 * 初始化
 */
void init_array(array * a);

/*
 * 客户端释放
 */
void release_array(array * a);

void add_array_item(array * a, int idx, int v);

int del_array_item(array * a, int idx);

int get_array_item(array * a, int idx);

int get_array_size(array * a);

int get_array_datanum(array * a);

#endif
