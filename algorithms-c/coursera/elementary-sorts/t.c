#include <stdio.h>

int ints[] = { 1, 2, 3 };
char cs[] = { 'x', 'y', 'z' };

void swap(void *a, void *b)
{
	int tmp = *((int *) a);
	*((int *) a) = *((int *) b);
	*((int *) b) = tmp;
}

int less(void *a, void *b)
{
	return *((int *) a) < *((int *) b);
}

int main()
{
	printf("%d < %d:%s\n", ints[0], ints[1],
	       less(ints, ints + 1) ? "yes" : "no");
	printf("%d < %d:%s\n", ints[2], ints[1],
	       less(ints + 2, ints + 1) ? "yes" : "no");
	printf("%d < %d:%s\n", ints[2], ints[0],
	       less(ints + 2, ints) ? "yes" : "no");
	swap(ints, ints + 2);
	swap(cs + 1, cs + 2);
	printf("%d - %d - %d\n", ints[0], ints[1], ints[2]);
	printf("%c - %c - %c\n", cs[0], cs[1], cs[2]);

	void *tp = ints;
	printf("%ld\n", sizeof(tp[0]));
	printf("%d - %d - %d\n", *((int *) tp), *((int *) (tp + 1)),
	       *((int *) (tp + 2)));
}
