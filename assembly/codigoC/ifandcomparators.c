#include <stdio.h>

int a = 0;
int b = 0;
int c = 0;
int d = 0;

int main () {


a = 8;
b = 5;
c = 7;
d = 7;


if (a > b)
  printf("%d", a);
else
  printf("%d",b);


if (a < b)
  printf("%d", a);
else
  printf("%d", b);


if (c >= d )
  printf("igual");
else
  printf("%d", c);

}
