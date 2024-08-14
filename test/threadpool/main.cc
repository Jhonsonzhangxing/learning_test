
#include <iostream>
#include"threadpool.h"
int main(){
    ThreadPool pool(4);

// enqueue and store future
auto result = pool.enqueue([](int answer) { return answer; }, 42);

// get result from future
std::cout << " pool.enqueue.. " << std::endl;
std::cout << result.get() << std::endl;
    return 0;
}