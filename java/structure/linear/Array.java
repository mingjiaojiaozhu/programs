package structure.linear;

import java.util.Arrays;

public class Array {
    private int[] _values = new int[64];
    private int _length = 0;
    private int _capacity = 64;

    public Array() {
        Arrays.fill(_values, 0);
    }

    public boolean isEmpty() {
        return 0 == _length;
    }

    public void add(int index, int value) {
        if (index < 0 || index > _length) {
            return;
        }

        if (_length >= _capacity) {
            _values = Arrays.copyOf(_values, _capacity + 16);
            Arrays.fill(_values, _capacity, _capacity + 16, 0);
            _capacity += 16;
        }

        for (int i = _length - 1; i >= index; --i) {
            _values[i + 1] = _values[i];
        }
        _values[index] = value;
        ++_length;
    }

    public void addHead(int value) {
        if (_length >= _capacity) {
            _values = Arrays.copyOf(_values, _capacity + 16);
            Arrays.fill(_values, _capacity, _capacity + 16, 0);
            _capacity += 16;
        }

        for (int i = _length - 1; i >= 0; --i) {
            _values[i + 1] = _values[i];
        }
        _values[0] = value;
        ++_length;
    }

    public void addTail(int value) {
        if (_length >= _capacity) {
            _values = Arrays.copyOf(_values, _capacity + 16);
            Arrays.fill(_values, _capacity, _capacity + 16, 0);
            _capacity += 16;
        }

        _values[_length] = value;
        ++_length;
    }

    public void erase(int index) {
        if (index < 0 || index >= _length) {
            return;
        }

        for (int i = index + 1; i < _length; ++i) {
            _values[i - 1] = _values[i];
        }
        --_length;
    }

    public void eraseHead() {
        if (0 == _length) {
            return;
        }

        for (int i = 1; i < _length; ++i) {
            _values[i - 1] = _values[i];
        }
        --_length;
    }

    public void eraseTail() {
        if (0 != _length) {
            --_length;
        }
    }

    public void set(int index, int value) {
        if (index >= 0 && index < _length) {
            _values[index] = value;
        }
    }

    public int get(int index) {
        if (index >= 0 && index < _length) {
            return _values[index];
        }
        return Integer.MIN_VALUE;
    }

    public void reverse() {
        int start = 0;
        int end = _length - 1;
        while (start < end) {
            _values[start] ^= _values[end];
            _values[end] ^= _values[start];
            _values[start] ^= _values[end];

            ++start;
            --end;
        }
    }

    public void clear() {
        Arrays.fill(_values, 0);
        _length = 0;
    }
}
