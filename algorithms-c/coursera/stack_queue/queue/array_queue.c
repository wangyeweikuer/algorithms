/**
 * 循环数组来实现队列
 */
#include <stddef.h>
#include "../arrays/arrays.h"
#include "queue.h"
#include "../errors.h"

void init_queue(queue* q){
	if(q->_array != NULL){
		printf("Can't init twice!\n");
		exit(ERR_INIT_TWICE);
	}
	q->_array = (arrays *) malloc(sizeof(arrays));
	init(q->_array);
	q->_end = -1;//-1表示没有可以删除的元素
	q->_first = 0;
}

void release_queue(queue* q){
	if(q->_array != NULL){
		release(q->_array);
		q->_end = -1;
		q->_first = 0;
	}
}

static int round_next(queue* q,int idx){
	int size = get_size(q->_array);
	return (idx + 1) % size;
}

static void do_resize(queue* q,int newsize){
	if(newsize != -1){
		int num = get_data_num(q->_array);
		resize(q->_array,newsize,q->_end,num);
		q->_first = num;
		q->_end = (num <= 0 ? -1 : 0);//这里有点特殊,正好将"num=0时置_end=-1"的情况也包括进去了
		printf("do_resize : %d-%d  --\n",q->_first,q->_end);
	}
}

void en_queue(queue* q,int v){
	int ns = need_resize_before_add(q->_array);
	do_resize(q,ns);
	add_item(q->_array,q->_first,v);
	if(q->_end < 0){
		q->_end = q->_first;
	}
	q->_first = round_next(q,q->_first);
	printf("en_queue : %d-%d  --\n",q->_first,q->_end);
}

int de_queue(queue* q){
	int v = del_item(q->_array,q->_end);
	int ns = need_resize_after_remove(q->_array);
	q->_end = round_next(q,q->_end);
	if(get_data_num(q->_array) == 0){
		q->_end = -1;
	}
	do_resize(q,ns);
	printf("de_queue : %d-%d  --\n",q->_first,q->_end);
	return v;
}

int get_queue_datanum(queue* q){
	return get_data_num(q->_array);
}

int get_queue_size(queue* q){
	return get_size(q->_array);
}

