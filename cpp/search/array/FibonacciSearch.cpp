#include <iostream>
#include <vector>
using namespace std;

class FibonacciSearch {
public:
    int search(vector<int> &nums, int target) {
        vector<int> fibonacci(2, 1);
        int index = 1;
        while ((int) nums.size() > fibonacci[index] - 1) {
            ++index;
            fibonacci.emplace_back(fibonacci[index - 1] + fibonacci[index - 2]);
        }

        vector<int> aux(nums.begin(), nums.end());
        aux.resize(fibonacci[index], nums.back());

        int start = 0;
        int end = nums.size() - 1;
        while (start <= end) {
            int middle = start + fibonacci[index - 1] - 1;
            if (target == aux[middle]) {
                return (middle >= (int) nums.size()) ? nums.size() - 1 : middle;
            }

            if (target < aux[middle]) {
                end = middle - 1;
                --index;
            } else {
                start = middle + 1;
                index -= 2;
            }
        }
        return -1;
    }
};
