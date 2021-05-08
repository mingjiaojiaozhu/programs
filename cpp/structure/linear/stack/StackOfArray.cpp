#include <iostream>
#include <vector>
using namespace std;

class StackOfArray {
public:
    StackOfArray() : values(vector<int>(64, 0)), length(0), capacity(64) {}

    bool isEmpty() {
        return !length;
    }

    void push(int value) {
        if (length >= capacity) {
            values.resize(capacity + 16, 0);
            capacity += 16;
        }

        values[length] = value;
        ++length;
    }

    int pop() {
        if (length) {
            --length;
            return values[length];
        }
        return INT_MIN;
    }

    void clear() {
        values.assign(capacity, 0);
        length = 0;
    }

private:
    vector<int> values;
    int length;
    int capacity;
};
