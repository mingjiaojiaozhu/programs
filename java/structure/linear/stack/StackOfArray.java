package structure.linear.stack;

import java.util.Arrays;

public class StackOfArray {
    private int[] _values = new int[64];
    private int _length = 0;
    private int _capacity = 64;

    public StackOfArray() {
        Arrays.fill(_values, 0);
    }

    public boolean isEmpty() {
        return 0 == _length;
    }

    public void push(int value) {
        if (_length >= _capacity) {
            _values = Arrays.copyOf(_values, _capacity + 16);
            Arrays.fill(_values, _capacity, _capacity + 16, 0);
            _capacity += 16;
        }

        _values[_length] = value;
        ++_length;
    }

    public int pop() {
        if (0 != _length) {
            --_length;
            return _values[_length];
        }
        return Integer.MIN_VALUE;
    }

    public void clear() {
        Arrays.fill(_values, 0);
        _length = 0;
    }
}
