#include <iostream>
#include <vector>
using namespace std;

class Hanoi {
public:
    void solution(vector<int> &values1, vector<int> &values2, vector<int> &values3) {
        move(values1.size(), values1, values2, values3);
    }

private:
    void move(int size, vector<int> &values1, vector<int> &values2, vector<int> &values3) {
        --size;
        if (!size) {
            values3.push_back(values1.back());
            values1.pop_back();
            return;
        }

        move(size, values1, values3, values2);
        values3.push_back(values1.back());
        values1.pop_back();
        move(size, values2, values1, values3);
    }
};
