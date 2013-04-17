#ifndef _queue_h_
#define _queue_h_

#include <stdlib.h>
#include <stdio.h>
#include "../arrays/arrays.h"

typedef struct{
	arrays * _array;
	int _first;//队列头元素(即将被删除的）的下标
	int _end;//队列尾元素之后(即将插入的）的下标
}queue;

/**
 *
 */
void init_queue(queue* q);
/**
 *
 */
void release_queue(queue* q);

/*
 * 给队列增加数据，
 */
void en_queue(queue* q,int v);
/*
 * 从队列中删除数据；
 */
int de_queue(queue* q);

/**
 * 返回数据量
 */
int get_queue_datanum(queue* q);

/**
 * 返回队列长度
 */
int get_queue_size(queue* q);

#endif
