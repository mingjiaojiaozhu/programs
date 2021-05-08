#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class LongestIncreasingSubsequence {
public:
    int solution(vector<int> &values) {
        vector<int> result(values.size(), 0);
        result[0] = 1;
        for (int i = 1; i < (int) values.size(); ++i) {
            result[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (values[i] > values[j] && result[i] < result[j] + 1) {
                    result[i] = result[j] + 1;
                }
            }
        }
        return *max_element(begin(result), end(result));
    }
};
