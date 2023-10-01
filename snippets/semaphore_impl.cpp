#include <mutex>
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include <condition_variable>

class semaphore {
private:
    int counter;
    std::mutex m;
    std::condition_variable cv;
public:
    void signal() {
        {
            std::lock_guard<std::mutex> guard(m);
            counter++;
        }
        cv.notify_all();
    }

    int wait() {
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul, [this]{ return this->counter > 0; });
        // here the lock is still owned by the thread
        return counter--;
    }
};

void produce(int id, semaphore* sem) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        sem->signal();
    }
}

void consume(int id, semaphore* sem) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(id));
        int item = sem->wait();
        std::cout << "consumer #" << id << "  gets item #" << item << std::endl; 
    }
}

int main() {
    std::vector<std::thread> vecs;
    semaphore s;
    for (int i = 0; i < 10; i++) {
        vecs.push_back(std::thread(produce, i, &s));
    }
    for (int i = 1; i < 6; i++) {
        vecs.push_back(std::thread(consume, i, &s));
    }

    for (auto &x: vecs) {
        x.join();
    }
}