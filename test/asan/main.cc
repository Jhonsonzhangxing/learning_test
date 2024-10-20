#include <stdio.h>
#include <stdlib.h>

// int main(void){
    
//     int array[10];
//     int i = 0;
//     while (i <= 10) {
//         array[i] = 1;
//         i++;
//     }

//     i = 0;
//     while (i <= 10) {
//         printf("%d ", array[i]);
//         i++;
//     }

//     printf("\n");

//     return 0;
// }
namespace demo {
  void DemoFunction() {
    int arr[10];                             // 定长数组大小11个int, 44个bytes
    for (int idx = 0; idx < 2000; idx++) {   // 越界发生在idx = 11的地方
      arr[idx] = idx * 2;
    }
  }
}

int main() {
  demo::DemoFunction();
  return 0;
}

// 用-fsanitize=address选项编译和链接你的程序;
// 用-fno-omit-frame-pointer编译，以在错误消息中添加更好的堆栈跟踪。
// 增加-O1以获得更好的性能。