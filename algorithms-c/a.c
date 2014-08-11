#include <stdio.h>

int next_id(){
	static int idx = 0;
	return idx++;
}

int main(){
	//printf("%d\n",idx);
	printf("%d\n",next_id());
	printf("%d\n",next_id());
	printf("%d\n",next_id());
	printf("%d\n",next_id());
	static idx ;
	printf("%d\n",idx);
}
