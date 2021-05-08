#include <iostream>
#include <vector>
using namespace std;

class PriorityQueue {
public:
    PriorityQueue() : values(vector<int>(64, 0)), length(0), capacity(64) {}

    bool isEmpty() {
        return !length;
    }

    void enqueue(int value) {
        if (length >= capacity) {
            values.resize(capacity + 16, 0);
            capacity += 16;
        }

        int child = length;
        while (child > 0) {
            int parent = (child - 1) >> 1;
            if (values[parent] <= value) {
                break;
            }
            values[child] = values[parent];
            child = parent;
        }
        values[child] = value;
        ++length;
    }

    int dequeue() {
        if (!length) {
            return INT_MIN;
        }

        --length;
        int value = values[0];
        int pivot = values[length];
        int parent = 0;
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
        return value;
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
