#include <stdio.h>
int main(void){
	char c = 'a';
	short s = 22;
	int i = 3;
	long l = 4;
	float f = 5;
	double d = 6;
	long double ld = 0;
	long long ll = 7;
	printf("%ld\n",sizeof(c));
	printf("%ld\n",sizeof(s));
	printf("%ld\n",sizeof(i));
	printf("%ld\n",sizeof(l));
	printf("%ld\n",sizeof(f));
	printf("%ld\n",sizeof(d));
	printf("%ld\n",sizeof(ld));
	printf("%ld\n",sizeof(ll));
}
