#include <stdio.h>
#include <malloc.h>
void test()
{
    sleep(1);
}
void f()
{
    int i;
    for( i = 0; i < 5; i ++)
        test();
}
int main()
{
    f();
    printf("process is over!\n");
    return 0;
}
