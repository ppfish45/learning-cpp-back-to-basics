#include <mutex>
#include <chrono>
#include <vector>
#include <thread>
#include <iostream>
#include <condition_variable>

// Write first
class RWLock {
private:

public:
    RWLock() : writerN(0), readerN(0), isWriting(false) {}

    void writerLock() {
        std::unique_lock<std::mutex> lock(wMutex);
        writerN++;
        wCv.wait(lock, [=](){ return this->readerN == 0 && !this->isWriting; });
        isWriting = true;
    }

    void writerUnlock() {
        {
            std::lock_guard<std::mutex> lock(wMutex);
            writerN--;
            isWriting = false;
        }
        if (writerN == 0) {
            rCv.notify_all();
        } else {
            wCv.notify_all();
        }
    }

    void readerLock() {
        std::unique_lock<std::mutex> lock(rMutex);
        rCv.wait(lock, [=](){ return this->writerN == 0 && !this->isWriting; });
        readerN++;
    }

    void readerUnlock() {
        {
            std::lock_guard<std::mutex> lock(rMutex);
            readerN--;
        }
        if (readerN == 0) {
            wCv.notify_all();
        }
    }

private:
    size_t writerN;
    size_t readerN;
    bool isWriting;
    std::mutex wMutex;
    std::condition_variable wCv;
    std::mutex rMutex;
    std::condition_variable rCv;
};

void readerThread(int id, RWLock *l) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        l->readerLock();
        std::cout << "reader #" << id << " starts" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        l->readerUnlock();
        std::cout << "reader #" << id << " finished" << std::endl;
    }
}

void writerThread(int id, RWLock *l) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        l->writerLock();
        std::cout << "writer #" << id << " starts" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        l->writerUnlock();
        std::cout << "writer #" << id << " finished" << std::endl;
    }
}

int main() {
    RWLock l;
    std::vector<std::thread> ths;
    for (int i = 0; i < 10; i++) {
        ths.emplace_back(readerThread, i, &l);
    }
    for (int i = 0; i < 3; i++) {
        ths.emplace_back(writerThread, i, &l);
    }
    for (auto &x: ths) {
        x.join();
    }
    return 0;
}