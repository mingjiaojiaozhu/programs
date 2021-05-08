package structure.tree.heap;

import java.util.Arrays;

public class BinaryHeap {
    private int[] _values = new int[64];
    private int _length = 0;
    private int _capacity = 64;

    public BinaryHeap() {
        Arrays.fill(_values, 0);
    }

    public boolean isEmpty() {
        return 0 == _length;
    }

    public void add(int value) {
        if (_length >= _capacity) {
            _values = Arrays.copyOf(_values, _capacity + 16);
            Arrays.fill(_values, _capacity, _capacity + 16, 0);
            _capacity += 16;
        }

        adjustHeapUp(_length, value);
        ++_length;
    }

    public void erase(int index) {
        if (index >= 0 && index < _length) {
            --_length;
            adjustHeapDown(index, _values[_length]);
        }
    }

    public void set(int index, int value) {
        if (index >= 0 && index < _length && value != _values[index]) {
            if (value < _values[index]) {
                adjustHeapUp(index, value);
            } else {
                adjustHeapDown(index, value);
            }
        }
    }

    public int get(int index) {
        if (index >= 0 && index < _length) {
            return _values[index];
        }
        return Integer.MIN_VALUE;
    }

    public void clear() {
        Arrays.fill(_values, 0);
        _length = 0;
    }

    private void adjustHeapUp(int child, int pivot) {
        while (child > 0) {
            int parent = (child - 1) >> 1;
            if (_values[parent] <= pivot) {
                break;
            }
            _values[child] = _values[parent];
            child = parent;
        }
        _values[child] = pivot;
    }

    private void adjustHeapDown(int parent, int pivot) {
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
    }
}
