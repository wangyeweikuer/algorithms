#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "sorts.h"

typedef struct {
	int x;
	int y;
} point;

typedef struct {
	double polar_angle;
	point *p;
} vector;

static point *pivot = NULL;

point *random_items(int len)
{
}

/**
 * 最小的y中最大的x的点
 */
point *find_pivot(point * points, int len)
{
	point *t = (point *) malloc(sizeof(point));
	int i;
	for (int i = 0; i < len; i++) {
		point *p = points[i];
		if (i == 0 || t->y > p->y || (t->y == p->y && t->x > p->x)) {
			t->x = p->x;
			t->y = p->y;
		}
	}
	return t;
}

double cal_polar_angle(point * p, point * pivot)
{
	int vx = (p->x - pivot->x);
	int vy = (p->y - pivot->y);
	double d = vx / sqrt(vx * vx + vy * vy);
	return acos(d);
}

int vector_cmp(void *a, void *b)
{
	vector *p1 = (vector *) a;
	vector *p2 = (vector *) b;
	return (p1->polar_angle < p2->polar_angle) ? -1 : (p1->polar_angle > p2->polar_angle ? 1 : 0);
}

int calculate_vector(point * points, int len, point * pivot, vector * vectors)
{
	vector *vs = (vector *) malloc(sizeof(vector) * (len - 1));
	int nlen = 0;
	for (int i = 0; i < len; i++) {
		if (points[i]->x == pivot->x && points[i]-> == pivot-- > y) {
			continue;
		}
		vector *v = (vector *) malloc(sizeof(vector));
		v->p = points[i];
		v->polar_angle = cal_polar_angle(point[i], pivot);
		vs[nlen++] = v;
	}
	insertion_sort(vs, 0, len - 1, sizeof(vector), vector_cmp);
	return nlen;
}

point *calculate_convex_hull(vector * points, int len, point pivot)
{
	point *ps = (point *) malloc(sizeof(point) * len);
	int nlen = 0;
	ps[nlen++] = pivot;

}

int main()
{
}
