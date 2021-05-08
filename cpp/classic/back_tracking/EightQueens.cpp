#include <iostream>
#include <vector>
#include <string>
using namespace std;

class EightQueens {
public:
    vector<vector<string>> solution(int num) {
        vector<vector<string>> result(0);
        vector<int> aux(num, -1);
        search(num, 0, 0, 0, 0, aux, result);
        return result;
    }

private:
    void search(int num, int row, int col, int left, int right, vector<int> &aux, vector<vector<string>> &result) {
        if (row == num) {
            vector<string> lines(0);
            for (int i = 0; i < num; i++) {
                string line(num, '0');
                line[aux[i]] = '1';
                lines.emplace_back(line);
            }
            result.push_back(lines);
            return;
        }

        int mask = ((1 << num) - 1) & (~(col | left | right));
        while (mask) {
            int pos = mask & (~mask + 1);
            mask &= (mask - 1);
            aux[row] = getBits(pos - 1);
            search(num, row + 1, col | pos, (left | pos) << 1, (right | pos) >> 1, aux, result);
            aux[row] = -1;
        }
    }

    int getBits(int value) {
        int result = 0;
        while (value) {
            ++result;
            value &= value - 1;
        }
        return result;
    }
};
