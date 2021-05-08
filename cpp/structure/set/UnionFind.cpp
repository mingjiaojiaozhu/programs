#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
public:
    UnionFind(int length) : length(length) {
        values.assign(length, -1);
        weights.assign(length, 1);
    }

    void add(int start, int end) {
        if (start < 0 || start >= length || end < 0 || end >= length) {
            return;
        }

        int rootStart = getRoot(start);
        int rootEnd = getRoot(end);
        if (rootStart != rootEnd) {
            if (weights[rootStart] < weights[rootEnd]) {
                values[rootEnd] = rootStart;
                weights[rootStart] += weights[rootEnd];
            } else {
                values[rootStart] = rootEnd;
                weights[rootEnd] += weights[rootStart];
            }
        }
    }

    bool contains(int start, int end) {
        if (start >= 0 && start < length && end >= 0 && end < length) {
            return getRoot(start) == getRoot(end);
        }
        return false;
    }

private:
    vector<int> values;
    vector<int> weights;
    int length;

    int getRoot(int value) {
        int root = value;
        while (~values[root]) {
            root = values[root];
        }

        while (value != root) {
            int aux = values[value];
            values[value] = root;
            value = aux;
        }
        return root;
    }
};
