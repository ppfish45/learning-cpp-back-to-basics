#include <vector>
#include <thread>
#include <iostream>
#include <shared_mutex>

int cnt;
uint64_t writeCnt;
uint64_t readCnt[10];
int op = 0;

std::shared_timed_mutex sharedMut;
std::mutex mut;

void writerFunc() {
    while (op == 0) {
        std::lock_guard<std::shared_timed_mutex> g(sharedMut);
        //std::lock_guard<std::mutex> g(mut);
        cnt++;
        writeCnt++;
    }
}

void readerFunc(int id) {
    while (op == 0) {
        sharedMut.lock_shared();
        //std::lock_guard<std::mutex> g(mut);
        readCnt[id]++;
        sharedMut.unlock_shared();
    }
}

int main() {
    std::vector<std::thread> threads;

    // add reader threads
    for (int i = 0; i < 10; i++) {
        threads.push_back(std::thread(readerFunc, i));
    }

    threads.push_back(std::thread(writerFunc));

    std::cin >> op;

    for (auto &th: threads) {
        th.join();
    }

    std::cout << "reader counts: " << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << readCnt[i] << " ";
    }
    std::cout << std::endl << "writer count:" << std::endl;
    std::cout << writeCnt << std::endl;
}