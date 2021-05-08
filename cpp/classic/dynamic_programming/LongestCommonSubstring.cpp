#include <iostream>
#include <vector>
#include <string>
using namespace std;

class LongestCommonSubstring {
public:
    int solution(string text1, string text2) {
        vector<vector<int>> result(text1.size() + 1, vector<int>(text2.size() + 1, 0));
        int maxValue = 0;
        for (int i = 1; i <= (int) text1.size(); ++i) {
            for (int j = 1; j <= (int) text2.size(); ++j) {
                result[i][j] = (text1[i - 1] == text2[j - 1]) ? result[i - 1][j - 1] + 1 : 0;
                if (maxValue < result[i][j]) {
                    maxValue = result[i][j];
                }
            }
        }
        return maxValue;
    }
};
