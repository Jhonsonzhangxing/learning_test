// #include <thread>
// #include <vector>
// #include <iostream>
// #include <atomic>
// #include <chrono>
// std::atomic_flag lock = ATOMIC_FLAG_INIT;
 
// void f(int n)
// {
//     while (lock.test_and_set(std::memory_order_acquire)) // 尝试获得锁
//     {
//         std::cout << "wait form thread " << n << std::endl;
//     }
//     std::cout << "thread " << n << " starts working" << std::endl;
// }
 
// void g(int n)
// {
//     std::cout << "thread " << n << " is going to start" << std::endl;
//     std::this_thread::sleep_for(std::chrono::milliseconds(1));
//     lock.clear();
//     std::cout << "thread " << n << " starts working" << std::endl;
// }

// std::atomic<int> foo(0);
 
// int main()
// {
//     lock.test_and_set();
//     std::thread t1(f, 1);
//     std::thread t2(g, 2);
 
//     t1.join();
//     t2.join();
// }


#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
 
std::atomic_flag lock = ATOMIC_FLAG_INIT;
 
void f(int n)
{
    for (int cnt = 0; cnt < 40; ++cnt)
    {
        while (lock.test_and_set(std::memory_order_acquire)) // 获取锁
        {
            std::cout << "thread: " << pthread_self()  << ",wait" << std::endl; 
        }
        static int out{};
        std::cout << n << ((++out % 40) == 0 ? '\n' : ' ');
        lock.clear(std::memory_order_release); // 释放锁
    }
}



 
int main()
{
    std::vector<std::thread> v;
    for (int n = 0; n < 10; ++n)
        v.emplace_back(f, n);
    for (auto& t : v)
        t.join();
}