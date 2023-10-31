#include <queue>
#include <atomic>
#include <vector>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <cmath>

class ProducerConsumerQueue{
public:
    void produce(int value){
        intensive_task();
        std::unique_lock<std::mutex> lock(mtx);
        queue.push(value);
        std::cout<< "Produced: " << value << std::endl;
        cond_var.notify_one();
    }

    int consume(){
        std::unique_lock<std::mutex> lock(mtx);
        while(queue.empty() ){
            cond_var.wait(lock);
        }
        int value = queue.front();
        
        queue.pop();

        return value;
    }

    double intensive_task() {
        double sum = 0.0;
        for (long long i = 0; i < 500000000; ++i) {
            sum += std::sqrt(i);
        }
        return sum;
    }

    bool check_queue(){
        return queue.empty();
    }

    void print_queue(){
        std::queue<int> tempQueue = queue; // 创建临时队列保存原始队列的副本
    
        // 打印临时队列中的所有元素
        while (!tempQueue.empty()) {
            std::cout << tempQueue.front() << " "; // 打印队首元素
            tempQueue.pop(); // 弹出队首元素
        }
    }

private:
    std::queue<int> queue;
    std::mutex mtx;
    std::condition_variable cond_var;
};

int main(){
    ProducerConsumerQueue pcQueue;
    std::atomic<int> active_producers(4);

    std::thread consumer([&]{
        while(true){
            int value = pcQueue.consume();
            std::cout << "        Consumed: " << value << std::endl;
            if(active_producers==0)
            {
                pcQueue.print_queue();
                break;
            }
        }
    });

    std::vector<std::thread> producers;
    for(int i=0; i<4; i++){
        producers.emplace_back([&](){
            for(int j=0; j<5; j++)
            {
                pcQueue.produce(j);
            }
            --active_producers;
        });
    }
    for(auto& producer:producers)
    {
        producer.join();
    }
    consumer.join();
    return 0;
}