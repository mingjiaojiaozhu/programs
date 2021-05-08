#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class IntervalCoverage {
public:
    int solution(vector<vector<int>> &values, vector<int> &target) {
        sort(values.begin(), values.end(), cmp);

        int start = target[0];
        int end = target[1];
        int index = 0;
        int result = 0;
        while (start < end) {
            int border = start;
            while (index < (int) values.size() && start >= values[index][0]) {
                if (border < values[index][1]) {
                    border = values[index][1];
                }
                ++index;
            }

            if (border == start) {
                return -1;
            }

            ++result;
            start = border;
        }
        return result;
    }

private:
    static bool cmp(const vector<int> &node1, const vector<int> &node2) {
        return node1[0] < node2[0];
    }
};
