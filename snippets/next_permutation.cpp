#include <vector>
#include <iostream>

bool next_permutation(std::vector<int> &num) {
    int n = num.size();
    int pivot = n - 1;
    while (pivot > 0 && num[pivot - 1] >= num[pivot]) {
        pivot --;
    }
    if (pivot == 0) {
        return false;
    } else {
        int target = pivot;
        while (target < n - 1 && num[target + 1] > num[pivot - 1]) {
            target ++;
        }
        std::swap(num[pivot - 1], num[target]);
        std::reverse(num.begin() + pivot, num.end());
    }
    return true;
}

int main() {
    std::vector<int> arr{1, 2, 3, 4, 5};
    do {
        for (int x : arr) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    } while (next_permutation(arr));
}