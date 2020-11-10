#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

std::mutex g_mutex;

int counter_no = 0;
int counter_mutex = 0;
std::atomic<int> counter_atomic = 0;


void counter_increase_no()
{
    uint16_t i = 5000;
    while(i > 0)
    {
        i--;
        counter_no++;
    }
}

void counter_increase_mutex()
{
    uint16_t i = 5000;
    while(i > 0)
    {
        i--;
        std::lock_guard<std::mutex> lock(g_mutex);
        counter_mutex++;
    }
}

void counter_increase_atomic()
{
    uint16_t i = 5000;
    while(i > 0)
    {
        i--;
        // std::lock_guard<std::mutex> lock(g_mutex);
        counter_atomic++;
    }
}

int main()
{
    auto start_time = std::chrono::steady_clock::now();
    std::thread t1 = std::thread(counter_increase_no);
    std::thread t2 = std::thread(counter_increase_no);
    t1.join();
    t2.join();
    auto end_time = std::chrono::steady_clock::now();
    auto duration_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time);
    std::cout << "[NO-MUTEX] couter:" << counter_no << std::endl;
    std::cout << "[NO-MUTEX] duration_time:" << duration_time.count() << " us"<< std::endl;


    start_time = std::chrono::steady_clock::now();
    t1 = std::thread(counter_increase_mutex);
    t2 = std::thread(counter_increase_mutex);
    t1.join();
    t2.join();
    end_time = std::chrono::steady_clock::now();
    duration_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time);
    std::cout << "[USE-MUTEX] couter:" << counter_mutex << std::endl;
    std::cout << "[USE-MUTEX] duration_time:" << duration_time.count() << " us"<< std::endl;


    start_time = std::chrono::steady_clock::now();
    t1 = std::thread(counter_increase_atomic);
    t2 = std::thread(counter_increase_atomic);
    t1.join();
    t2.join();
    end_time = std::chrono::steady_clock::now();
    duration_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time);
    std::cout << "[USE-ATOMIC] couter:" << counter_atomic << std::endl;
    std::cout << "[USE-ATOMIC] duration_time:" << duration_time.count() << " us"<< std::endl;

    return 0;
}