#include "stdio.h"
#include "stdlib.h"
int matrix[9][9];
int all[9][9][9];
int allnum[9][9];

void print_data()
{
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; ++j) {
			printf("%d", matrix[i][j] + 1);
		}
		printf("\n");
	}
	printf("\n");
	//put_if_can()
}

void read_data()
{
	int i, j, k;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; ++j) {
			scanf("%d", &matrix[i][j]);
			matrix[i][j]--;
			for (k = 0; k < 9; ++k) {
				all[i][j][k] = 0;
			}
			if (matrix[i][j] == -1) {
				allnum[i][j] = 0;
			} else {
				allnum[i][j] = 9;
			}
		}
	}
	print_data();
}

//纵向
void add_to_vertical(int i, int j, int v)
{
	int k;
	for (k = 0; k < 9; ++k) {
		if (matrix[k][j] == -1) {
			int p = all[k][j][v];
			all[k][j][v] = 1;
			if (p == 0) {
				allnum[k][j]++;
			}
		}
	}
}

//横向
void add_to_horizontal(int i, int j, int v)
{
	int k;
	for (k = 0; k < 9; ++k) {
		if (matrix[i][k] == -1) {
			int p = all[i][k][v];
			all[i][k][v] = 1;
			if (p == 0) {
				allnum[i][k]++;
			}
		}
	}
}

//当前格子
void add_to_grid(int i, int j, int v)
{
	int k, h;
	for (k = 0; k < 3; ++k) {
		int nx = i / 3 * 3 + k;
		for (h = 0; h < 3; ++h) {
			int ny = j / 3 * 3 + h;
			if (matrix[nx][ny] == -1) {
				int p = all[nx][ny][v];
				all[nx][ny][v] = 1;
				if (p == 0) {
					allnum[nx][ny]++;
				}
			}
		}
	}
}

void init()
{
	int i, j;
	for (i = 0; i < 9; ++i) {
		for (j = 0; j < 9; ++j) {
			int v = matrix[i][j];
			if (v != -1) {
				add_to_horizontal(i, j, v);
				add_to_vertical(i, j, v);
				add_to_grid(i, j, v);
			}
		}
	}
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			printf("%d,%d,%d\n", i, j, allnum[i][j]);
		}
	}
	printf("init over\n");
}

int findLast(int i, int j)
{
	int k;
	for (k = 0; k < 9; ++k) {
		if (all[i][j][k] == 0) {
			return k;
		}
	}
	return -1;
}

//横向
int must_put_vertical(int i, int j)
{
	int k, has[9], h;
	for (k = 0; k < 9; k++) {
		has[k] = all[i][j][k];
	}
	for (k = 0; k < 9; k++) {
		if (j != k && matrix[i][k] == -1) {
			for (h = 0; h < 9; h++) {
				if (all[i][k][h] == 0) {
					has[h] = 1;
				}
			}
		}
	}
	for (k = 0; k < 9; k++) {
		if (has[h] == 0) {
			return k;
		}
	}
	return -1;
}

// 纵向
int must_put_horizontal(int i, int j)
{
	int k, has[9], h;
	for (k = 0; k < 9; k++) {
		has[k] = all[i][j][k];
	}
	for (k = 0; k < 9; k++) {
		if (i != k && matrix[k][j] == -1) {
			for (h = 0; h < 9; h++) {
				if (all[k][j][h] == 0) {
					has[h] = 1;
				}
			}
		}
	}
	for (k = 0; k < 9; k++) {
		if (has[h] == 0) {
			return k;
		}
	}
	return -1;
}

int must_put_grid(int i, int j)
{
	int k, has[9], h, p;
	for (k = 0; k < 9; k++) {
		has[k] = all[i][j][k];
	}
	for (k = 0; k < 3; k++) {
		int nx = i / 3 * 3 + k;
		for (p = 0; p < 3; p++) {
			int ny = j / 3 * 3 + p;
			if ((i != nx || j != ny) && matrix[nx][ny] == -1) {
				for (h = 0; h < 9; h++) {
					if (all[nx][ny][h] == 0) {
						has[h] = 1;
					}
				}
			}
		}
	}
	for (k = 0; k < 9; k++) {
		if (has[h] == 0) {
			return k;
		}
	}
	return -1;
}

int put_if_can(int i, int j)
{
	int v = findLast(i, j);
	int ok = 0;
	if (allnum[i][j] == 8) {
		ok = 1;
	} else if ((v = must_put_vertical(i, j)) != -1) {
		ok = 1;
	} else if ((v = must_put_grid(i, j)) != -1) {
		ok = 1;
	} else if ((v = must_put_horizontal(i, j)) != -1) {
		ok = 1;
	}
	if (ok == 1) {
		add_to_vertical(i, j, v);
		add_to_horizontal(i, j, v);
		add_to_grid(i, j, v);
		matrix[i][j] = v;
		all[i][j][v] = 1;
		allnum[i][j] = 9;
	}
}

void calculate()
{
	while (1) {
		int count = 81;
		int i, j;
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				if (allnum[i][j] == 9) {
					count--;
					continue;
				}
				put_if_can(i, j);
			}
		}
		printf("count:%d\n", count);
		if (count == 0) {
			break;
		}
	}
}

int main(int argc, char const *argv[])
{
	while (1) {
		printf("start ...\n");
		read_data();
		init();
		calculate();
		print_data();
		printf("end ...\n\n");
	}
	return 0;
}
