#include <stdio.h>
#include <stddef.h>
#include <unistd.h>


void printi(int i){
    printf("\n i = %d", i);
}

int main(){
    int i = 0;

    while(1){
    	printi(i);
    	sleep(1);
	i++;
    }
	
    return 0;
}
