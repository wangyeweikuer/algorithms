#include "union_find_set.h"
int find_root_node(int p){
	return id[p];
}
void union_node(int p,int q){
	int c = id[p];
	for (int i = 0; i < LEN; ++i)
	{
		if(id[i] == c){
			id[i] = id[q];
		}
	}	
}
void init_node(){
	for (int i = 0; i < LEN; ++i)
	{
		id[i] = i;
	}
}
void print_node(){
	for (int i = 0; i < LEN; ++i)
	{
		if(i>0){
			printf(" ");
		}
		printf("%d", id[i]);
	}
	printf("\n");
}
void read_and_union_node(){
	int p,q;
	while(scanf("%d-%d",&p,&q) != EOF){
		union_node(p,q);
	}
}
int main(int argc, char const *argv[])
{
	init_node();
	read_and_union_node();
	print_node();
	return 0;
}
