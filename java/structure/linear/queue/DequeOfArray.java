package structure.linear.queue;

import java.util.Arrays;

public class DequeOfArray {
    private int[] _values = new int[64];
    private int _head = 0;
    private int _tail = 0;
    private int _capacity = 64;

    public DequeOfArray() {
        Arrays.fill(_values, 0);
    }

    public boolean isEmpty() {
        return _head == _tail;
    }

    public void enqueueHead(int value) {
        if ((_tail + 1) % _capacity == _head) {
            int[] aux = new int[_capacity + 16];
            if (_head < _tail) {
                System.arraycopy(_values, _head, aux, 0, _tail - _head);
            } else {
                System.arraycopy(_values, _head, aux, 0, _capacity - _head);
                System.arraycopy(_values, 0, aux, _capacity - _head, _tail);
            }
            Arrays.fill(aux, _capacity, _capacity + 16, 0);
            _values = aux;
            _head = 0;
            _tail = _capacity - 1;
            _capacity += 16;
        }

        _head = (0 != _head) ? _head - 1 : _capacity - 1;
        _values[_head] = value;
    }

    public void enqueueTail(int value) {
        if ((_tail + 1) % _capacity == _head) {
            int[] aux = new int[_capacity + 16];
            if (_head < _tail) {
                System.arraycopy(_values, _head, aux, 0, _tail - _head);
            } else {
                System.arraycopy(_values, _head, aux, 0, _capacity - _head);
                System.arraycopy(_values, 0, aux, _capacity - _head, _tail);
            }
            Arrays.fill(aux, _capacity, _capacity + 16, 0);
            _values = aux;
            _head = 0;
            _tail = _capacity - 1;
            _capacity += 16;
        }

        _values[_tail] = value;
        _tail = (_tail + 1) % _capacity;
    }

    public int dequeueHead() {
        if (_head != _tail) {
            int value = _values[_head];
            _head = (_head + 1) % _capacity;
            return value;
        }
        return Integer.MIN_VALUE;
    }

    public int dequeueTail() {
        if (_head != _tail) {
            _tail = (0 != _tail) ? _tail - 1 : _capacity - 1;
            return _values[_tail];
        }
        return Integer.MIN_VALUE;
    }

    public void clear() {
        Arrays.fill(_values, 0);
        _head = 0;
        _tail = 0;
    }
}
