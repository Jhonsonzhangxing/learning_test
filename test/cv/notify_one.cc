#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>
using namespace std::chrono_literals;
 
std::condition_variable cv;
std::mutex cv_m;
int i = 0;
bool done = false;
 
void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cout << "等待... \n";
    cv.wait(lk, []{ return i == 1; });
    std::cout << "...结束等待; i == " << i << '\n';
    done = true;
}

//  void wait() {
//     std::unique_lock<std::mutex> lk(cv_m);
//     cv.wait(lk, []{ return i == 1;});
//  }
 
void signals()
{
    std::this_thread::sleep_for(200ms);
    std::cout << "假通知...\n";
    cv.notify_one(); // 等待线程被通知且 i == 0。
                     // cv.wait 被唤醒，检查 i，再回到等待
 
    std::unique_lock<std::mutex> lk(cv_m);
    i = 1;
    while (!done) 
    {
        std::cout << "真的改动通知...\n";
        lk.unlock();
        cv.notify_one(); // 等待线程被通知且 i == 1，cv.wait 返回
        std::this_thread::sleep_for(300ms);
        lk.lock();
    }
}
 
int main()
{
    std::thread t1(waits), t2(signals);
    t1.join(); 
    t2.join();
}