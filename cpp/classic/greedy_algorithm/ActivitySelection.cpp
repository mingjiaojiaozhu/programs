#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class ActivitySelection {
public:
    int solution(vector<vector<int>> &values) {
        sort(values.begin(), values.end(), cmp);

        int end = values[0][1];
        int result = 1;
        for (int i = 1; i < (int) values.size(); ++i) {
            if (end <= values[i][0]) {
                end = values[i][1];
                ++result;
            }
        }
        return result;
    }

private:
    static bool cmp(const vector<int> &node1, const vector<int> &node2) {
        return node1[1] < node2[1];
    }
};
