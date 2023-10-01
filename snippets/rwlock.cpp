#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <condition_variable>

enum RWLOCK_TYPE {
    READ,
    WRITE
};

template<RWLOCK_TYPE> class RWLock;

template<>
class RWLock<READ> {
// reader first
private:
    int writerN;
    bool isWriting;
    int readerN;
    std::mutex lock;
    std::condition_variable writerCv;
    std::condition_variable readerCv;

public:
    RWLock<READ>(): writerN(0), isWriting(false), readerN(0) {}

    void writer_lock() {
        std::unique_lock<std::mutex> g(lock);
        ++writerN;
        writerCv.wait(g, [this](){ return this->readerN == 0 && !this->isWriting; });
        isWriting = true;
    }

    void writer_unlock() {
        std::unique_lock<std::mutex> g(lock);
        --writerN;
        isWriting = false;
        if (writerN > 0 && this->readerN == 0) {
            writerCv.notify_one();
        } else {
            readerCv.notify_all();
        }
    }

    void reader_lock() {
        std::unique_lock<std::mutex> g(lock);
        ++readerN;
        readerCv.wait(g, [this](){ return !this->isWriting; });
    }

    void reader_unlock() {
        std::unique_lock<std::mutex> g(lock);
        --readerN;
        if (readerN == 0 && writerN > 0) {
            writerCv.notify_one();
        }
    }
};

template<>
class RWLock<WRITE> {
// writer first
private:
    int writerN; // wait + writing, mutual exclusion between read & write
    int readerN;
    bool isWriting; // assure mutual exclusion of write
    std::mutex lock;
    std::condition_variable writerCv;
    std::condition_variable readerCv;

public:
    RWLock<WRITE>(): writerN(0), readerN(0) {}

    void writer_lock() {
        std::unique_lock<std::mutex> g(lock);
        ++writerN;
        writerCv.wait(g, [this](){ return this->readerN == 0 && !this->isWriting; });
        isWriting = true;
    }

    void writer_unlock() {
        std::unique_lock<std::mutex> g(lock);
        --writerN;
        isWriting = false;
        if (writerN > 0) {
            writerCv.notify_one();
        } else {
            readerCv.notify_all();
        }
    }

    void reader_lock() {
        std::unique_lock<std::mutex> g(lock);
        readerCv.wait(g, [this](){ return this->writerN == 0; });
        ++readerN;
    }

    void reader_unlock() {
        std::unique_lock<std::mutex> g(lock);
        --readerN;
        if (readerN == 0 && writerN > 0) {
            writerCv.notify_one();
        }
    }
};

template<RWLOCK_TYPE T>
void read(int id, RWLock<T>* l) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        l->reader_lock();
        std::cout << "reader #" << id << "  started" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "reader #" << id << "  finished" << std::endl;
        l->reader_unlock();        
    }
}

template<RWLOCK_TYPE T>
void write(int id, RWLock<T>* l) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        l->writer_lock();
        std::cout << "writer #" << id << "  starts" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "writer #" << id << "  finished" << std::endl;
        l->writer_unlock();        
    }
}

int main() {
    std::vector<std::thread> ths;
    RWLock<RWLOCK_TYPE::READ> l;

    for (int i = 0; i < 10; i++) {
        ths.push_back(std::thread(read<READ>, i, &l));
    }

    for (int i = 0; i < 3; i++) {
        ths.push_back(std::thread(write<READ>, i, &l));
    }

    for (auto &x: ths) {
        x.join();
    }

    return 0;
}