#include <stdio.h>

int a = 0;
int i = 0;
int c = 0;
int b[3] = {7,3,5};


int main () {

b[1] = 4;
printf("%d", b[1]);

c = 3 + b[1];
printf("%d\n\n", c);

while (i < 3){
  a = a + b[i];
  i = i + 1;
  printf("%d", a);
}

}
