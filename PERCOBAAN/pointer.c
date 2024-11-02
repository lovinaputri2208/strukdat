#include <stdio.h>
#include <conio.h>

int main(){

 int i = 5, j = 10;
 int *px;
 int **ppx;


 px = &i;
 ppx = &px;
 *px = 3;
 **ppx = 7;
 px = &j;
 **ppx = 9;

scanf("%d", &j);
 printf("Secara langsung %d\n", i );
 printf("Secara langsung %d\n", j );
 printf("Nilai pointer 1 : %d\n", *px);
printf("Nilai Pointer 2: %d", **ppx);

 getch();
}


