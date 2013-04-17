#include <stdio.h>
#define WLEN 5
#define HLEN 5
int maze[WLEN][HLEN] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0
};

struct point {
	int x;
	int y;
} stack[512];
int top = 0;
void push(struct point p)
{
	stack[top++] = p;
}

struct point pop()
{
	return stack[--top];
}

int dfs(int x, int y)
{
	struct point p = { x, y };
	push(p);
	maze[x][y] = 2;
	if (x == WLEN - 1 && y == HLEN - 1) {
		return 1;
	}
	if (x - 1 >= 0 && maze[x - 1][y] == 0) {
		int r = dfs(x - 1, y);
		if (r == 1)
			return 1;
	}
	if (x + 1 < WLEN && maze[x + 1][y] == 0) {
		int r = dfs(x + 1, y);
		if (r == 1)
			return 1;
	}
	if (y - 1 >= 0 && maze[x][y - 1] == 0) {
		int r = dfs(x, y - 1);
		if (r == 1)
			return 1;
	}
	if (y + 1 < HLEN && maze[x][y + 1] == 0) {
		int r = dfs(x, y + 1);
		if (r == 1)
			return 1;
	}
	maze[x][y] = 0;
	pop();
	return 0;
}

int main(void)
{
	int res = dfs(0, 0);
	int i = 0;
	for (; i < top; i++) {
		printf("%d,%d\n", stack[i].x, stack[i].y);
	}
	int j;
	for(i=0;i<WLEN;i++){
		for(j=0;j<HLEN;j++){
			printf("%d ",maze[i][j]);
		}
		printf("\n");
	}
	return 0;
}
