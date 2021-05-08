#include <iostream>
#include <vector>
using namespace std;

class Array {
public:
    Array() : values(vector<int>(64, 0)), length(0), capacity(64) {}

    bool isEmpty() {
        return !length;
    }

    void add(int index, int value) {
        if (index < 0 || index > length) {
            return;
        }

        if (length >= capacity) {
            values.resize(capacity + 16, 0);
            capacity += 16;
        }

        for (int i = length - 1; i >= index; --i) {
            values[i + 1] = values[i];
        }
        values[index] = value;
        ++length;
    }

    void addHead(int value) {
        if (length >= capacity) {
            values.resize(capacity + 16, 0);
            capacity += 16;
        }

        for (int i = length - 1; i >= 0; --i) {
            values[i + 1] = values[i];
        }
        values[0] = value;
        ++length;
    }

    void addTail(int value) {
        if (length >= capacity) {
            values.resize(capacity + 16, 0);
            capacity += 16;
        }

        values[length] = value;
        ++length;
    }

    void erase(int index) {
        if (index < 0 || index >= length) {
            return;
        }

        for (int i = index + 1; i < length; ++i) {
            values[i - 1] = values[i];
        }
        --length;
    }

    void eraseHead() {
        if (!length) {
            return;
        }

        for (int i = 1; i < length; ++i) {
            values[i - 1] = values[i];
        }
        --length;
    }

    void eraseTail() {
        if (length) {
            --length;
        }
    }

    void set(int index, int value) {
        if (index >= 0 && index < length) {
            values[index] = value;
        }
    }

    int get(int index) {
        if (index >= 0 && index < length) {
            return values[index];
        }
        return INT_MIN;
    }

    void reverse() {
        int start = 0;
        int end = length - 1;
        while (start < end) {
            swap(values[start], values[end]);

            ++start;
            --end;
        }
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
