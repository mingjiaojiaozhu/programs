#include <iostream>
#include <vector>
using namespace std;

class RoundRobinSchedule {
public:
    vector<vector<int>> solution(int k) {
        int size = (int) pow(2, k);
        vector<vector<int>> result(0);
        for (int i = 0; i < size; ++i) {
            result.emplace_back(vector<int>(size, i));
        }
        schedule(size, 0, 0, result);
        return result;
    }

private:
    void schedule(int size, int startRow, int startCol, vector<vector<int>> &result) {
        size >>= 1;
        if (size > 1) {
            schedule(size, startRow, startCol, result);
            schedule(size, startRow + size, startCol, result);
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result[startRow + size + i][startCol + size + j] = result[startRow + i][startCol + j];
                result[startRow + i][startCol + size + j] = result[startRow + size + i][startCol + j];
            }
        }
    }
};
