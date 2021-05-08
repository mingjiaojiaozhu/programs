#include <iostream>
#include <vector>
#include <string>
using namespace std;

class LongestPalindromicSubstring {
public:
    string solution(string text) {
        vector<vector<bool>> aux(text.size(), vector<bool>(text.size(), false));
        for (int i = 0; i < (int) text.size(); ++i) {
            aux[i][i] = true;
        }

        int start = 0;
        int size = 1;
        for (int i = 1; i < (int) text.size(); ++i) {
            for (int j = 0; j < (int) text.size() - i; ++j) {
                int index = i + j;
                aux[j][index] = (1 == i) ? (text[j] == text[index]) : (text[j] == text[index] && aux[j + 1][index - 1]);
                if (aux[j][index] && size < i + 1) {
                    start = j;
                    size = i + 1;
                }
            }
        }
        return text.substr(start, size);
    }
};
