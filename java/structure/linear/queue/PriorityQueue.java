package structure.linear.queue;

import java.util.Arrays;

public class PriorityQueue {
    private int[] _values = new int[64];
    private int _length = 0;
    private int _capacity = 64;

    public PriorityQueue() {
        Arrays.fill(_values, 0);
    }

    public boolean isEmpty() {
        return 0 == _length;
    }

    public void enqueue(int value) {
        if (_length >= _capacity) {
            _values = Arrays.copyOf(_values, _capacity + 16);
            Arrays.fill(_values, _capacity, _capacity + 16, 0);
            _capacity += 16;
        }

        int child = _length;
        while (child > 0) {
            int parent = (child - 1) >> 1;
            if (_values[parent] <= value) {
                break;
            }
            _values[child] = _values[parent];
            child = parent;
        }
        _values[child] = value;
        ++_length;
    }

    public int dequeue() {
        if (0 == _length) {
            return Integer.MIN_VALUE;
        }

        --_length;
        int value = _values[0];
        int pivot = _values[_length];
        int parent = 0;
        while (true) {
            int child = (parent << 1) + 1;
            if (child >= _length) {
                break;
            }

            if (child < _length - 1 && _values[child] > _values[child + 1]) {
                ++child;
            }
            if (_values[child] >= pivot) {
                break;
            }
            _values[parent] = _values[child];
            parent = child;
        }
        _values[parent] = pivot;
        return value;
    }

    public void clear() {
        Arrays.fill(_values, 0);
        _length = 0;
    }
}
