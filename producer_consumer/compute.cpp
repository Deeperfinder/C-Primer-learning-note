#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <mutex>

const int num_threads = 4;
double total_sum = 0.0;
std::mutex mtx;

void intensive_task(long long start, long long end) {
    double sum = 0.0;
    for (long long i = start; i < end; ++i) {
        sum += std::sqrt(i);
    }
    mtx.lock();
    total_sum += sum;
    mtx.unlock();
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::thread threads[num_threads];
    long long task_size = 8000000000 / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(intensive_task, i * task_size, (i+1) * task_size);
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "Task completed in: " << elapsed.count() << " seconds" << std::endl;
    std::cout << "Result: " << total_sum << std::endl;

    return 0;
}
