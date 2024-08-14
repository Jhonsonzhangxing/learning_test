#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
    while(1) {
        int* p = (int*)malloc(40);
        sleep(100);
    }
    return 0;
}
// ps -o majflt,minflt -C test1