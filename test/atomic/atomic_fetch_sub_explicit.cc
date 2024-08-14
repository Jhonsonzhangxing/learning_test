#include <atomic>
#include <iostream>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

const int N = 50;
std::atomic<int> cnt;
std::vector<int> data(N);

void reader(int id) {
    for (;;) {
        int idx = atomic_fetch_sub_explicit(&cnt, 1, std::memory_order_acquire);
        if (idx >= 0) {
            std::cout << "reader " << std::to_string(id) << " deal with " << std::to_string(data[idx]) << ", idx: " << idx  << " ,cnt " << cnt << std::endl;
        } else {
            std::cout << " reader " << std::to_string(id) << " done" << std::endl;
            break;
        }
    }
}

int main() {
    std::iota(data.begin(),data.end(), 1);
    cnt = data.size() -1;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(reader,i);
    }
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}