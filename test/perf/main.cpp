#include <iostream>
#include <vector>
using namespace std;

void pushvec( std::vector<int>& vecs, int i){
        while(true) {
        pushvec(vecs,i);
        std::cout << "i: " << i++ << std::endl;
    }
}

int main(){

    std::vector<int> vecs;
    int i = 0;
    pushvec(vecs,i);

    return 0;
}
//使用 perf record采样 $pid 进程的事件，数据默认保存在当前目录下，名为perf.data（或-o 指定）。
//perf report -i perf.data 生成报告
//perf record -g -p $pid -o /xdata/log/latest/perf.data
//perf report -i perf.data