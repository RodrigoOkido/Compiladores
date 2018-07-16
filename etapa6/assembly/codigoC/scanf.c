#include <stdio.h>


int a = 1;
int b = 1;
int v = 0;

int main(){
	scanf("%d", &v);
	while(a < 10){
		v = v + b;
		printf("%d\n", v);
		a = a + 1;
	}
}
