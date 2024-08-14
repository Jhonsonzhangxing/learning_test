#include <iostream>
#include <future>
#include <chrono>

bool is_prime(int x) {
    for (int i = 2; i < x; ++i) {
        if (x % i ==0) {
            return false;
        }
    }
    return true;
}

void print_int(std::future<int>& fut) {
    std::cout << "starting print_int\n";
    int x = fut.get();
    std::cout << "value: " << x << "\n";
}
int countdown(int from, int to) {
    for (int i = from; i != to; --i) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Lift off!\n";
    return from - to;
}

int main() {
    // std::future<bool> fut = std::async(is_prime, 444444443);

    // std::cout << "checking please wait";
    // std::chrono::milliseconds span(100);
    // while (fut.wait_for(span) == std::future_status::timeout) {
    //     std::cout << "." << std::flush;
    // }
    // bool x = fut.get();
    // std::cout << "\n444444443 " << (x ? "is" : "is not") << " prime.\n";

    // std::promise<int> prom;
    // std::future<int> fut = prom.get_future();
    // std::thread th(print_int, std::ref(fut));
    // std::this_thread::sleep_for(std::chrono::seconds(5));
    // prom.set_value(10);
    // th.join();

    std::packaged_task<int(int,int)> tsk(countdown);
    std::future<int> ret = tsk.get_future();

    std::thread th(std::move(tsk),10,0);

    int value = ret.get();
    std::cout << "The countdown lasted for " << value << " seconds.\n";
    th.join();



    return 0;
}