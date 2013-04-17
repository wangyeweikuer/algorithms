#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
/** 数组元素 */
struct snode {
	struct snode *next;
	int value;
};
struct linked_stack {
	struct snode *head;
} *stack;

void init_stack()
{
	if (stack != NULL) {
		printf("Error to init twice !\n");
		exit(1);
	}
	//这里的写法错误，在c中struct分配在栈中，这个tmp的地址，再下次函数进入时，可能会被其他变量占用，从而产生错误；
	//struct linked_stack tmp = {NULL};
	//这里的写法错误，在c中struct分配在栈中，这个tmp的地址，再下次函数进入时，可能会被其他变量占用，从而产生错误；
	//stack = &tmp;
	stack = (struct linked_stack *) malloc(sizeof(struct linked_stack));	//记得释放
	stack->head = NULL;
}

void release_stack()
{
	free(stack);
}

struct snode *_create_new(int v)
{
	struct snode *tmp = (struct snode *) malloc(sizeof(struct snode));
	tmp->next = NULL;
	tmp->value = v;
	return tmp;
}

void push_stack(int v)
{
	//这里的写法错误，在c中struct分配在栈中，这个tmp的地址，再下次函数进入时，可能会被其他变量占用，从而产生错误；
	//struct snode tmp = { NULL, v };
	struct snode *tmp = _create_new(v);
	if (stack->head == NULL) {
		//stack->head = &tmp;
		stack->head = tmp;
	} else {
		//tmp.next = stack->head->next;
		//stack->head = &tmp;
		tmp->next = stack->head;
		stack->head = tmp;
	}
}

int pop_stack(int *v)
{
	if (stack->head == NULL) {
		return 0;
	}
	(*v) = stack->head->value;
	struct snode *tmp = stack->head;
	stack->head = stack->head->next;
	free(tmp);		//释放元素空间，因为元素分配在堆区
	return 1;
}

int get_data_num()
{
	int num = 0;
	struct snode *n = stack->head;
	while (n != NULL) {
		n = n->next;
		num++;
	}
	return num;
}

int get_stack_size()
{
	return get_data_num();
}
