#include <stdio.h>
void partition(int *array ,int f,int e,int m){
	if(e <= f) return;
	int v = array[m];
	m = e;
	array[m] = array[e--];
	while(e >= f){
		while(e >= f && array[f] >= v) f++;
		if(e >= f) {
			array[m] = array[f];
			m = f++;
		}
		while(e >= f && array[e] < v) e--;
		if(e >= f){
			array[m] = array[e];
			m = e--;
		}
	}
	array[m] = v;	
}

int main(){
	:
}
