#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
 
std::atomic<bool> lock(false); // 锁定时持有 true，解锁时持有 false
 
int new_line{1}; // 访问通过原子锁变量同步
 
void f(int n)
{
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        while (std::atomic_exchange_explicit(&lock, true, std::memory_order_acquire))
            ; // 获取前自旋
        std::cout << n << (new_line++ % 30 ? "" : "\n");
        std::atomic_store_explicit(&lock, false, std::memory_order_release);
    }
}
 
// int main()
// {
//     std::vector<std::thread> v;
//     for (int n = 0; n < 8; ++n)
//         v.emplace_back(f, n);
//     for (auto& t : v)
//         t.join();
// }

#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
 
using namespace std::chrono_literals;
 
// cnt 的含义：
//  5：读者和写者在竞争中。无活跃读者或写者。
//  4...0：有 1...5 个读者活跃。写者被阻塞。
// -1：写者赢得竞争。读者被阻塞。
 
const int N = 5; // 允许四个共时读者
std::atomic<int> cnt(N);
 
std::vector<int> data;
// std::atomic<bool> lock(false);
 
void reader(int id)
{
    for(;;)
    {
        // 锁定
        // while (std::atomic_fetch_sub(&cnt, 1) <= 0)
        //     std::atomic_fetch_add(&cnt, 1);
       while(std::atomic_exchange_explicit(&lock,true,std::memory_order_acquire))
        //    std::cout << "读者 检查 " + std::to_string(id) << std::endl;
        ;
 
        // 读取
        if (!data.empty())
            std::cout << ("读者 " + std::to_string(id) +
                          " 看见 " + std::to_string(*data.rbegin()) + '\n');

 
        // 解锁
        std::atomic_exchange_explicit(&lock,false,std::memory_order_release);
 
        // 暂停
        // std::cout << "读者: " << std::to_string(id) << " lock: " << lock << std::endl;
        std::this_thread::sleep_for(1ms);
        if (data.size() == 25)
            break;
    }
}
 
void writer()
{
    for(int n = 0; n < 25; ++n)
    {
        // 锁定
        // while (std::atomic_fetch_sub(&cnt, N + 1) != N)
        //     std::atomic_fetch_add(&cnt, N + 1);
        while(std::atomic_exchange_explicit(&lock,true,std::memory_order_acquire))
            ;
        // 写入
        data.push_back(n);
        std::cout << "写者写入 " << n << '\n';
 
        // 解锁
        // std::atomic_fetch_add(&cnt, N + 1);
 
        // 暂停
        // std::this_thread::sleep_for(1ms);
         std::atomic_exchange_explicit(&lock,false,std::memory_order_release);
        //  std::cout << "writer out: " << lock << std::endl;
         std::this_thread::sleep_for(1ms);
        // std::this_thread::yield();
    }
    // std::cout << "writer out: " << lock << std::endl;
}
 
int main()
{
    std::vector<std::thread> v;
    for (int n = 0; n < N; ++n)
        v.emplace_back(reader, n);
    v.emplace_back(writer);
    // std::cout << "begin sleep" << std::endl;
//  std::this_thread::sleep_for(10000ms);
//  std::cout << "end sleep" << std::endl;
    for (auto& t : v)
    {
        if (t.joinable()){
            
            t.join();
            std::cout << "join..." << std::endl;
        }
        
    }
}
       