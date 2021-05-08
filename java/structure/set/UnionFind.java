package structure.set;

import java.util.Arrays;

public class UnionFind {
    private int[] _values = null;
    private int[] _weights = null;
    private int _length = 0;

    public UnionFind(int length) {
        _values = new int[length];
        Arrays.fill(_values, -1);
        _weights = new int[length];
        Arrays.fill(_weights, 1);
        _length = length;
    }

    public void add(int start, int end) {
        if (start < 0 || start >= _length || end < 0 || end >= _length) {
            return;
        }

        int rootStart = getRoot(start);
        int rootEnd = getRoot(end);
        if (rootStart != rootEnd) {
            if (_weights[rootStart] < _weights[rootEnd]) {
                _values[rootEnd] = rootStart;
                _weights[rootStart] += _weights[rootEnd];
            } else {
                _values[rootStart] = rootEnd;
                _weights[rootEnd] += _weights[rootStart];
            }
        }
    }

    public boolean contains(int start, int end) {
        if (start >= 0 && start < _length && end >= 0 && end < _length) {
            return getRoot(start) == getRoot(end);
        }
        return false;
    }

    private int getRoot(int value) {
        int root = value;
        while (0 != ~_values[root]) {
            root = _values[root];
        }

        while (value != root) {
            int aux = _values[value];
            _values[value] = root;
            value = aux;
        }
        return root;
    }
}
