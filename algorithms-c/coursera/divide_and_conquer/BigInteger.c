#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stddef.h>

#define MAX_LEN 10005

typedef struct {
	int len;
	char *digits;
} BigInteger;

BigInteger *_allocate(int len)
{
	if (len <= 0 || len >= MAX_LEN) {
		printf("The len[%d] isn't valid!\n", len);
		exit(1);
	}
	BigInteger *i = (BigInteger *) malloc(sizeof(BigInteger));
	if (i == NULL) {
		printf("Memory leak!\n");
		exit(1);
	}
	i->digits = (char *) malloc(sizeof(char) * len);
	if (i->digits == NULL) {
		printf("Memory leak!\n");
		exit(1);
	}
	return i;
}

void _release(BigInteger * i)
{
	if (i == NULL) {
		return;
	}
	free(i->digits);
	free(i);
}

void print(BigInteger * integer)
{
	int i = integer->len;
	while (i) {
		printf("%c", integer->digits[--i] + '0');
	}
}

int compare(BigInteger * i1, BigInteger * i2)
{
	if (i1->len != i2->len)
		return i1->len - i2->len;
	int i = i1->len;
	while ((--i) > -1) {
		if (i1->digits[i] != i2->digits[i])
			return (int) (i1->digits[i] - i2->digits[i]);
	}
	return 0;
}

BigInteger *read_int()
{
	char *cs = (char *) malloc(sizeof(char) * MAX_LEN);
	scanf("%s", cs);
	int len = strlen(cs);
	BigInteger *c = _allocate(len);
	c->len = len;
	for (int i = len - 1; i >= 0; i--) {
		c->digits[i] = cs[len - 1 - i] - '0';
	}
	free(cs);
	return c;
}

BigInteger *naive_multiple(BigInteger * a, BigInteger * b)
{
	BigInteger *c = _allocate(a->len + b->len);
	c->len = a->len + b->len;
	int i, j, k;
	for (i = 0; i < c->len; i++) {
		c->digits[i] = 0;
	}
	for (i = 0; i < a->len; i++) {
		for (j = 0; j < b->len; j++) {
			k = a->digits[i] * b->digits[j] + c->digits[i + j];
			c->digits[i + j] = k % 10;
			c->digits[i + j + 1] += k / 10;
		}
	}
	while (c->len > 1 && c->digits[c->len - 1] == 0) {
		c->len--;
	}
	return c;
}

/**
 * a = x1*10^n+x2
 * b = x3*10^n+x4
 * a*b = (x1*x3)*10^2n + ((x1+x2)*(x3*x4)-x1*x3-x2*x4)*10^n + x2*x4
 */
BigInteger * gauss_multiple(BigInteger *a ,BigInteger *b)
{
	if(a->len * b->len <= 100){
		return naive_multiple(a,b);
	}

}

int main(void *args)
{
	printf("Input int a:");
	BigInteger *a = read_int();
	printf("Input int b:");
	BigInteger *b = read_int();
	BigInteger *c = naive_multiple(a, b);
	printf("Output int c:");
	print(c);
	printf("\n");
	_release(a);
	_release(b);
	_release(c);
}

//void add_to(BigInteger * dest,BigInteger 
