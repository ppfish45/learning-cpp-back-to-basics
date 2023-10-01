#include <random>
#include <cassert>
#include <iostream>
#include <unordered_map>

const size_t mapSizes[30] = {7, 17, 37, 79, 163, 331, 673, 1361, 2729, 5471, 10949, 21911, 43853, 87719, 175447, 350899, 701819, 1403641, 2807303, 5614657, 11229331, 22458671, 44917381, 89834777, 179669557, 359339171, 718678369, 1437356741};

class hashMap {
private:
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;
    };

    Node** buckets;
    int nBuckets;
    int bucketSizeIdx;
    int nElements;

    void __insert__(int k, int v) {
        int bucketId = k % nBuckets;
        if (buckets[bucketId] == nullptr) {
            buckets[bucketId] = new Node{k, v, nullptr, nullptr};
            return;
        }
        Node* cur = buckets[bucketId];
        while (cur->next != nullptr && cur->key != k) {
            cur = cur->next;
        }
        if (cur->key == k) {
            cur->value = v;
            return;
        }
        Node* newNode = new Node{k, v, nullptr, nullptr};
        cur->next = newNode;
        newNode->prev = cur;
    }

    void __remove__(int k) {
        int bucketId = k % nBuckets;
        if (buckets[bucketId] == nullptr) {
            return;
        }
        Node* cur = buckets[bucketId];
        while (cur->next != nullptr && cur->key != k) {
            cur = cur->next;
        }
        if (cur->key != k) {
            return;
        }
        if (cur->prev) {
            cur->prev->next = cur->next;
        } else {
            buckets[bucketId] = cur->next;
        }
        if (cur->next) {
            cur->next->prev = cur->prev;
        }
        delete cur;
    }

    int __get__(int k) {
        int bucketId = k % nBuckets;
        if (buckets[bucketId] == nullptr) {
            return -1;
        }
        Node* cur = buckets[bucketId];
        while (cur->next != nullptr && cur->key != k) {
            cur = cur->next;
        }
        if (cur->key != k) {
            return -1;
        }
        return cur->value;
    }

    void __remap__() {
        Node** oldBuckets = buckets;
        int oldNBuckets = nBuckets;

        bucketSizeIdx++;
        nBuckets = mapSizes[bucketSizeIdx];
        buckets = new Node*[nBuckets];

        for (int i = 0; i < oldNBuckets; i++) {
            Node* cur = oldBuckets[i];
            while (cur != nullptr) {
                __insert__(cur->key, cur->value);
                Node* nex = cur->next;
                delete cur;
                cur = nex;
            }
        }
    }

public:
    hashMap() {
        bucketSizeIdx = 0;
        nElements = 0;
        nBuckets = mapSizes[bucketSizeIdx];
        buckets = new Node*[nBuckets];
    }

    void put(int k, int v) {
        __insert__(k, v);
        if (++nElements > nBuckets) {
            __remap__();
        }
    }

    int get(int k) {
        return __get__(k);
    }

    void remove(int k) {
        __remove__(k);
    }
};

int main() {
    std::unordered_map<int, int> m1;
    hashMap m2;
    
    int op = 100000;
    while (op --) {
        int x = rand() % 137;
        int y = rand();
        if (op % 10 > 7) {
            // add
            m1[x] = y;
            m2.put(x, y);
        } else {
            // delete
            m1.erase(x);
            m2.remove(x);
        }
        int qr = rand() % 137;        
        int r1 = -1;
        int r2 = m2.get(qr);
        if (m1.find(qr) != m1.end()) {
            r1 = m1[qr];
        }
        assert(r1 == r2);
    }

    return 0;
}