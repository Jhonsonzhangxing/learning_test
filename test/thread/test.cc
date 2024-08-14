#include <iostream>
#include <thread>
#include <chrono>

void independent_thread() {
    std::cout << "Running independent thread_id: " << pthread_self() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Independent thread finished" << std::endl;
}

void threadcaller() {
    std::cout << "start caller thread..id: " << pthread_self() <<std::endl;
    std::thread t(independent_thread);
    t.detach();
    // t.join();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "exit caller thread.." << std::endl;
}


int main() {
    threadcaller();
    std::this_thread::sleep_for(std::chrono::seconds(6));
    return 0;
}