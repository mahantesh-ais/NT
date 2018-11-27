#include<stdio.h>
#include<stdlib.h>

int main(){
    int a;
    int *p;
    a = 10;
    p = &a;

    if(-1)
    	printf("\n %p is the output of printing a pointer \n", p);
    return 0;
}
