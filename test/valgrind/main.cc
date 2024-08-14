#include <stdlib.h>
#include <malloc.h>
#include <string.h>
 
void test()
{
    int *ptr = (int*)malloc(sizeof(int)*10);
 
    // ptr[10] = 7; // 内存越界
 
    memcpy(ptr +1, ptr, 5); // 踩内存
 
 
    // free(ptr); 
    // free(ptr);// 重复释放
 
    // int *p1;
    // *p1 = 1; // 非法指针
    free(ptr) ;
}
 
int main(void)
{
    test();
    return 0;
}
