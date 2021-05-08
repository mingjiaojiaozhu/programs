package structure.graph;

import java.util.Arrays;

public class GraphOfAdjacencyList {
    private VertexNode[] _graphs = new VertexNode[64];
    private int _length = 0;
    private int _capacity = 64;

    public GraphOfAdjacencyList() {
        Arrays.fill(_graphs, null);
    }

    public boolean isEmpty() {
        return 0 == _length;
    }

    public void addEdge(int index, int edgeIndex, int weight) {
        if (index < 0 || index >= _length || edgeIndex < 0 || edgeIndex >= _length || index == edgeIndex) {
            return;
        }

        if (null == _graphs[index].next) {
            _graphs[index].next = new EdgeNode(edgeIndex, weight);
            return;
        }

        EdgeNode edge = _graphs[index].next;
        while (null != edge.next) {
            if (edgeIndex == edge.index) {
                edge.weight = weight;
                return;
            }
            edge = edge.next;
        }
        if (edgeIndex == edge.index) {
            edge.weight = weight;
        } else {
            edge.next = new EdgeNode(edgeIndex, weight);
        }
    }

    public void addVertex(int value) {
        if (_length >= _capacity) {
            _graphs = Arrays.copyOf(_graphs, _capacity + 16);
            Arrays.fill(_graphs, _capacity, _capacity + 16, null);
            _capacity += 16;
        }

        _graphs[_length] = new VertexNode(value);
        ++_length;
    }

    public void eraseEdge(int index, int edgeIndex) {
        if (index < 0 || index >= _length || edgeIndex < 0 || edgeIndex >= _length || index == edgeIndex) {
            return;
        }

        EdgeNode edge = _graphs[index].next;
        if (null == edge) {
            return;
        }
        if (edgeIndex == edge.index) {
            _graphs[index].next = edge.next;
            return;
        }

        while (null != edge.next) {
            if (edgeIndex == edge.next.index) {
                edge.next = edge.next.next;
                return;
            }
            edge = edge.next;
        }
    }

    public void eraseVertex(int index) {
        if (index < 0 || index >= _length) {
            return;
        }

        for (int i = 0; i < _length; ++i) {
            if (i != index) {
                eraseEdge(i, index);
            }
        }

        for (int i = index + 1; i < _length; ++i) {
            _graphs[i - 1] = _graphs[i];
        }
        --_length;
        _graphs[_length] = null;
    }

    public void setEdge(int index, int edgeIndex, int weight) {
        if (index < 0 || index >= _length || edgeIndex < 0 || edgeIndex >= _length || index == edgeIndex) {
            return;
        }

        EdgeNode edge = _graphs[index].next;
        while (null != edge && edgeIndex != edge.index) {
            edge = edge.next;
        }

        if (null != edge) {
            edge.weight = weight;
        }
    }

    public void setVertex(int index, int value) {
        if (index >= 0 && index < _length) {
            _graphs[index].value = value;
        }
    }

    public int getEdge(int index, int edgeIndex) {
        if (index < 0 || index >= _length || edgeIndex < 0 || edgeIndex >= _length || index == edgeIndex) {
            return Integer.MIN_VALUE;
        }

        EdgeNode edge = _graphs[index].next;
        while (null != edge && edgeIndex != edge.index) {
            edge = edge.next;
        }

        if (null != edge) {
            return edge.weight;
        }
        return Integer.MIN_VALUE;
    }

    public int getVertex(int index) {
        if (index >= 0 && index < _length) {
            return _graphs[index].value;
        }
        return Integer.MIN_VALUE;
    }

    public void clear() {
        Arrays.fill(_graphs, null);
        _length = 0;
    }

    private class EdgeNode {
        public int index = 0;
        public int weight = 0;
        public EdgeNode next = null;

        public EdgeNode(int index, int weight) {
            this.index = index;
            this.weight = weight;
        }
    }

    private class VertexNode {
        public int value = 0;
        public EdgeNode next = null;

        public VertexNode(int value) {
            this.value = value;
        }
    }
}
