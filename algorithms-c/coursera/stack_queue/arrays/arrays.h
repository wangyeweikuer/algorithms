#ifndef _arrays_h_
#define _arrays_h_

#include <stddef.h>

/*
 * 完成通用的数组内存管理代码；
 * 内部函数和内部成员变量，都用static限定，内部变量前加_做区别
 */
typedef struct {
	int *_data;		//数据数组
	int _size;		//数组长度
	int _num;		//有效数据的数量
} arrays;

/**
 * 判断在增加前是否需要重新调整数组
 * @return 返回-1表示不需要，返回大于0的值表示需要重新分配的大小
 */
int need_resize_before_add(arrays * a);

/**
 * 判断在移除之后是否需要重新调整数组
 * @return 返回-1表示不需要，返回大于0的值表示需要重新分配的大小
 */
int need_resize_after_remove(arrays * a);

/*
 * 调整数组大小，重新分配;自动处理原来数组有循环使用的情况；新的数据从0开始分配
 */
void resize(arrays * a, int newsize, int cp_idx, int cp_length);

/**
 * 初始化
 */
void init(arrays * a);

/*
 * 客户端释放
 */
void release(arrays * a);

void add_item(arrays * a, int idx, int v);

int del_item(arrays * a, int idx);

int get_size(arrays * a);

int get_data_num(arrays * a);

#endif
