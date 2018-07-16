#include <stdio.h>

int a = 0;
int b = 0;
int c = 4;
int x = 5;
int y = 8;
int v[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };



int soma(int x , int y){

  a = x + y;
  return a;

}


int main () {

b = soma(c, v[2]);
printf("%d",b);

}
