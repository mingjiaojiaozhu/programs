#include <iostream>
#include <vector>
using namespace std;

class DequeOfArray {
public:
    DequeOfArray() : values(vector<int>(64, 0)), head(0), tail(0), capacity(64) {}

    bool isEmpty() {
        return head == tail;
    }

    void enqueueHead(int value) {
        if ((tail + 1) % capacity == head) {
            vector<int> aux(capacity + 16, 0);
            if (head < tail) {
                copy(values.begin() + head, values.begin() + tail, aux.begin());
            } else {
                copy(values.begin() + head, values.begin() + capacity, aux.begin());
                copy(values.begin(), values.begin() + tail, aux.begin() + capacity - head);
            }
            values = aux;
            head = 0;
            tail = capacity - 1;
            capacity += 16;
        }

        head = head ? head - 1 : capacity - 1;
        values[head] = value;
    }

    void enqueueTail(int value) {
        if ((tail + 1) % capacity == head) {
            vector<int> aux(capacity + 16, 0);
            if (head < tail) {
                copy(values.begin() + head, values.begin() + tail, aux.begin());
            } else {
                copy(values.begin() + head, values.begin() + capacity, aux.begin());
                copy(values.begin(), values.begin() + tail, aux.begin() + capacity - head);
            }
            values = aux;
            head = 0;
            tail = capacity - 1;
            capacity += 16;
        }

        values[tail] = value;
        tail = (tail + 1) % capacity;
    }

    int dequeueHead() {
        if (head != tail) {
            int value = values[head];
            head = (head + 1) % capacity;
            return value;
        }
        return INT_MIN;
    }

    int dequeueTail() {
        if (head != tail) {
            tail = tail ? tail - 1 : capacity - 1;
            return values[tail];
        }
        return INT_MIN;
    }

    void clear() {
        values.assign(capacity, 0);
        head = 0;
        tail = 0;
    }

private:
    vector<int> values;
    int head;
    int tail;
    int capacity;
};
