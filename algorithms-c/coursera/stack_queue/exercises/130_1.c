#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "../stack/stack.h"
#define MAXLEN 100
int readline(int *cs)
{
	char c;
	int n = 0;
	while (scanf("%c", &c) != EOF && c != '\n') {
		if (c == ' ') {
			continue;
		}
		cs[n++] = (int) (c - 'A');
	}
	return n;
}

int main()
{
	int cs[MAXLEN];
	int len = 0;
	printf("Please input chars :\n");
	while ((len = readline(cs)) != 0) {
		stack tmp = { 0, 0 };
		stack *s = &tmp;
		init_stack(s);
		int i = 0;
		int ins = -1;
		int top = -1;
		while (i < len) {
			if (top < cs[i]) {
				push_stack(s, (top = ++ins));
				printf("push %d; ", top);
			} else if (top == cs[i]) {
				if (get_stack_datanum(s) == 0) {
					printf("Can't do it:a!\n");
					break;
				}
				printf("pop %d; ", pop_stack(s));
				top =
				    (get_stack_datanum(s) >
				     0 ? get_stack_top(s) : -1);
				i++;
			} else {
				printf("Can't do it:b!\n");
				break;
			}
		}
		if (i == len) {
			printf("OK!\n");
		}
		release_stack(s);
		s = NULL;
		printf("Please input chars :\n");
	}
	return 0;
}
