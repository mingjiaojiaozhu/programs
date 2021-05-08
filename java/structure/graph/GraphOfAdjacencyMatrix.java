package structure.graph;

import java.util.Arrays;

public class GraphOfAdjacencyMatrix {
    private int[] _vertexes = new int[64];
    private int[][] _edges = new int[64][64];
    private int _length = 0;
    private int _capacity = 64;

    public GraphOfAdjacencyMatrix() {
        Arrays.fill(_vertexes, 0);
        for (int i = 0; i < 64; ++i) {
            Arrays.fill(_edges[i], 0);
        }
    }

    public boolean isEmpty() {
        return 0 == _length;
    }

    public void addEdge(int index, int edgeIndex, int weight) {
        if (index >= 0 && index < _length && edgeIndex >= 0 && edgeIndex < _length && index != edgeIndex) {
            _edges[index][edgeIndex] = weight;
        }
    }

    public void addVertex(int value) {
        if (_length >= _capacity) {
            _vertexes = Arrays.copyOf(_vertexes, _capacity + 16);
            Arrays.fill(_vertexes, _capacity, _capacity + 16, 0);
            for (int i = 0; i < _capacity; ++i) {
                _edges[i] = Arrays.copyOf(_edges[i], _capacity + 16);
                Arrays.fill(_edges[i], _capacity, _capacity + 16, 0);
            }
            _edges = Arrays.copyOf(_edges, _capacity + 16);
            for (int i = _capacity; i < _capacity + 16; ++i) {
                _edges[i] = new int[_capacity + 16];
                Arrays.fill(_edges[i], 0);
            }
            _capacity += 16;
        }

        _vertexes[_length] = value;
        ++_length;
    }

    public void eraseEdge(int index, int edgeIndex) {
        if (index >= 0 && index < _length && edgeIndex >= 0 && edgeIndex < _length && index != edgeIndex) {
            _edges[index][edgeIndex] = 0;
        }
    }

    public void eraseVertex(int index) {
        if (index < 0 || index >= _length) {
            return;
        }

        for (int i = 0; i < index; ++i) {
            for (int j = index + 1; j < _length; ++j) {
                _edges[i][j - 1] = _edges[i][j];
            }
        }
        for (int i = index + 1; i < _length; ++i) {
            for (int j = 0; j < index; ++j) {
                _edges[i - 1][j] = _edges[i][j];
            }
            for (int j = index + 1; j < _length; ++j) {
                _edges[i - 1][j - 1] = _edges[i][j];
            }
        }

        for (int i = index + 1; i < _length; ++i) {
            _vertexes[i - 1] = _vertexes[i];
        }
        --_length;
    }

    public void setEdge(int index, int edgeIndex, int weight) {
        if (index >= 0 && index < _length && edgeIndex >= 0 && edgeIndex < _length && index != edgeIndex && 0 != _edges[index][edgeIndex]) {
            _edges[index][edgeIndex] = weight;
        }
    }

    public void setVertex(int index, int value) {
        if (index >= 0 && index < _length) {
            _vertexes[index] = value;
        }
    }

    public int getEdge(int index, int edgeIndex) {
        if (index >= 0 && index < _length && edgeIndex >= 0 && edgeIndex < _length && index != edgeIndex && 0 != _edges[index][edgeIndex]) {
            return _edges[index][edgeIndex];
        }
        return Integer.MIN_VALUE;
    }

    public int getVertex(int index) {
        if (index >= 0 && index < _length) {
            return _vertexes[index];
        }
        return Integer.MIN_VALUE;
    }

    public void clear() {
        Arrays.fill(_vertexes, 0);
        for (int i = 0; i < _capacity; ++i) {
            Arrays.fill(_edges[i], 0);
        }
        _length = 0;
    }
}
