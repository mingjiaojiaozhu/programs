#include <iostream>
#include <vector>
using namespace std;

class Sudoku {
public:
    void solution(vector<vector<int>> &nums) {
        vector<int> lines(nums.size(), 0);
        vector<int> columns(nums.size(), 0);
        vector<vector<int>> blocks(nums.size() / 3, vector<int>(nums.size() / 3, 0));
        for (int i = 0; i < (int) nums.size(); ++i) {
            for (int j = 0; j < (int) nums.size(); ++j) {
                if (nums[i][j]) {
                    fill(lines, columns, blocks, i, j, nums[i][j] - 1);
                }
            }
        }

        while (true) {
            bool flag = false;
            for (int i = 0; i < (int) nums.size(); ++i) {
                for (int j = 0; j < (int) nums.size(); ++j) {
                    if (!nums[i][j]) {
                        int mask = ~(lines[i] | columns[j] | blocks[i / 3][j / 3]) & 0x1ff;
                        if (!(mask & (mask - 1))) {
                            int digit = getBits(mask - 1);
                            fill(lines, columns, blocks, i, j, digit);
                            nums[i][j] = digit + 1;
                            flag = true;
                        }
                    }
                }
            }
            if (!flag) {
                break;
            }
        }

        vector<pair<int, int>> spaces(0);
        for (int i = 0; i < (int) nums.size(); ++i) {
            for (int j = 0; j < (int) nums.size(); ++j) {
                if (!nums[i][j]) {
                    spaces.emplace_back(i, j);
                }
            }
        }
        search(nums, lines, columns, blocks, spaces, 0, false);
    }

private:
    bool search(vector<vector<int>> &nums, vector<int> &lines, vector<int> &columns, vector<vector<int>> &blocks, vector<pair<int, int>> &spaces, int index, bool flag) {
        if (index == spaces.size()) {
            return true;
        }

        int row = spaces[index].first;
        int col = spaces[index].second;
        int mask = ~(lines[row] | columns[col] | blocks[row / 3][col / 3]) & 0x1ff;
        while (mask && !flag) {
            int pos = mask & (~mask + 1);
            mask &= (mask - 1);
            int digit = getBits(pos - 1);
            fill(lines, columns, blocks, row, col, digit);
            nums[row][col] = digit + 1;
            flag = search(nums, lines, columns, blocks, spaces, index + 1, flag);
            fill(lines, columns, blocks, row, col, digit);
        }
        return flag;
    }

    void fill(vector<int> &lines, vector<int> &columns, vector<vector<int>> &blocks, int row, int col, int digit) {
        lines[row] ^= (1 << digit);
        columns[col] ^= (1 << digit);
        blocks[row / 3][col / 3] ^= (1 << digit);
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
