#include <iostream>
#include <vector>
#include <string>
using namespace std;

class LevenshteinDistance {
public:
    int solution(string text1, string text2) {
        vector<vector<int>> result(text1.size() + 1, vector<int>(text2.size() + 1, 0));
        result[0][1] = 1;
        result[1][0] = 1;
        for (int i = 1; i <= (int) text1.size(); ++i) {
            for (int j = 1; j <= (int) text2.size(); ++j) {
                int value = (text1[i - 1] == text2[j - 1]) ? 0 : 1;
                result[i][j] = min(min(result[i - 1][j] + 1, result[i][j - 1] + 1), result[i - 1][j - 1] + value);
            }
        }
        return result.back().back();
    }
};
