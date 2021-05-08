#include <iostream>
#include <vector>
using namespace std;

class BinaryHeap {
public:
    BinaryHeap() : values(vector<int>(64, 0)), length(0), capacity(64) {}

    bool isEmpty() {
        return !length;
    }

    void add(int value) {
        if (length >= capacity) {
            vector<int> aux(capacity + 16, 0);
            copy(values.begin(), values.end(), aux.begin());
            values = aux;
            capacity += 16;
        }

        adjustHeapUp(length, value);
        ++length;
    }

    void erase(int index) {
        if (index >= 0 && index < length) {
            --length;
            adjustHeapDown(index, values[length]);
        }
    }

    void set(int index, int value) {
        if (index >= 0 && index < length && value != values[index]) {
            if (value < values[index]) {
                adjustHeapUp(index, value);
            } else {
                adjustHeapDown(index, value);
            }
        }
    }

    int get(int index) {
        if (index >= 0 && index < length) {
            return values[index];
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

    void adjustHeapUp(int child, int pivot) {
        while (child > 0) {
            int parent = (child - 1) >> 1;
            if (values[parent] <= pivot) {
                break;
            }
            values[child] = values[parent];
            child = parent;
        }
        values[child] = pivot;
    }

    void adjustHeapDown(int parent, int pivot) {
        while (true) {
            int child = (parent << 1) + 1;
            if (child >= length) {
                break;
            }

            if (child < length - 1 && values[child] > values[child + 1]) {
                ++child;
            }
            if (values[child] >= pivot) {
                break;
            }
            values[parent] = values[child];
            parent = child;
        }
        values[parent] = pivot;
    }
};
