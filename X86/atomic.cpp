#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <sched.h>
#include <vector>

const int num_threads = 52; // 设置线程数量
const int num_iterations = 1000000; // 设置每个线程执行的原子操作次数

std::atomic<int> counter(0);




void setAffinity(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) != 0) {
        std::cerr << "Failed to set CPU affinity." << std::endl;
    }
}

void increment(int core_id) {
    setAffinity(core_id);
//    std::atomic<int> counter(0);
    for (int i = 0; i < num_iterations; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    std::thread threads[num_threads];
    std::vector<int> core_ids = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 1, 3, 5, 7, 9, 11, 13, 15, 17 ,19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51}; // 设置每个线程要绑定的核心

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(increment, core_ids[i]);
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    //std::cout << "Total count: " << counter.load() << std::endl;
    std::cout << "Total time: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}

