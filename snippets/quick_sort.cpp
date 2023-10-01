#include <vector>
#include <iostream>

void qsort(std::vector<int>& A, int l, int r) {
    if (l >= r) return;
    std::swap(A[l], A[(l + r) >> 1]);
    int pivot = A[l];
    int ls = l;
    int rs = r - 1;
    for (int i = l + 1; i <= rs;) {
        if (A[i] <= pivot) {
            A[ls++] = A[i];
            i ++;
        } else {
            std::swap(A[i], A[rs--]);
        }
    }
    A[ls+1] = pivot;
    qsort(A, l, ls);
    qsort(A, ls + 2, r);
}

int main() {
    std::vector<int> A{1, 5, 2, 3, 10, 9, 8, 1, 9, 3, 4, 5};
    qsort(A, 0, A.size());
    for (auto x: A) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}