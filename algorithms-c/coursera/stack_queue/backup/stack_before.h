/*
 * 初始化操作
 */
void init_stack();

/*
 * 释放
 */
void release_stack();

/**
 * push an element into stack
 */
void push_stack(int v);

/**
 * @return 堆栈中有数据时返回1，否则返回0;
 */
int pop_stack(int *v);

/**
 * 堆栈中的数据量
 */
int get_data_num();

/*
 * 堆栈大小
 */
int get_stack_size();
