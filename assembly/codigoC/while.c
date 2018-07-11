#include <stdio.h>

int a = 0;
int b = 1;
int d = 0;
int e = 0;
int v[9] = {1,2,3,4,5,6,7,9};
float t = 3.2;
float c = 0.2;
char f = 'p';

int operator () {

	a = 1 + 5;
	b = 5 - 3;
	d = a * 5;
	e = b/2;


}

int conditional1 (int num)
{

	if (a < b)
	 	a = 3;
	else
		printf ("j");

}

int conditional2 (){
	if( d > e )
	 	return 0;

	return 1;
}


float returntest(int address, int pointer){
	c = 5.3;

	return c;
}


int while_test() {
	while (a > 0){
		a = a + 1;
	}
	return 0;

}
