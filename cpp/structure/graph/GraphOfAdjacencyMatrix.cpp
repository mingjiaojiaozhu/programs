#include <iostream>
#include <vector>
using namespace std;

class GraphOfAdjacencyMatrix {
public:
    GraphOfAdjacencyMatrix() : vertexes(vector<int>(64, 0)), length(0), capacity(64) {
        for (int i = 0; i < 64; ++i) {
            edges.emplace_back(vector<int>(64, 0));
        }
    }

    bool isEmpty() {
        return !length;
    }

    void addEdge(int index, int edgeIndex, int weight) {
        if (index >= 0 && index < length && edgeIndex >= 0 && edgeIndex < length && index != edgeIndex) {
            edges[index][edgeIndex] = weight;
        }
    }

    void addVertex(int value) {
        if (length >= capacity) {
            vertexes.resize(capacity + 16, 0);
            for (vector<int> &edge : edges) {
                edge.resize(capacity + 16, 0);
            }
            edges.resize(capacity + 16, vector<int>(capacity + 16, 0));
            capacity += 16;
        }

        vertexes[length] = value;
        ++length;
    }

    void eraseEdge(int index, int edgeIndex) {
        if (index >= 0 && index < length && edgeIndex >= 0 && edgeIndex < length && index != edgeIndex) {
            edges[index][edgeIndex] = 0;
        }
    }

    void eraseVertex(int index) {
        if (index < 0 || index >= length) {
            return;
        }

        for (int i = 0; i < index; ++i) {
            for (int j = index + 1; j < length; ++j) {
                edges[i][j - 1] = edges[i][j];
            }
        }
        for (int i = index + 1; i < length; ++i) {
            for (int j = 0; j < index; ++j) {
                edges[i - 1][j] = edges[i][j];
            }
            for (int j = index + 1; j < length; ++j) {
                edges[i - 1][j - 1] = edges[i][j];
            }
        }

        for (int i = index + 1; i < length; ++i) {
            vertexes[i - 1] = vertexes[i];
        }
        --length;
    }

    void setEdge(int index, int edgeIndex, int weight) {
        if (index >= 0 && index < length && edgeIndex >= 0 && edgeIndex < length && index != edgeIndex && edges[index][edgeIndex]) {
            edges[index][edgeIndex] = weight;
        }
    }

    void setVertex(int index, int value) {
        if (index >= 0 && index < length) {
            vertexes[index] = value;
        }
    }

    int getEdge(int index, int edgeIndex) {
        if (index >= 0 && index < length && edgeIndex >= 0 && edgeIndex < length && index != edgeIndex && edges[index][edgeIndex]) {
            return edges[index][edgeIndex];
        }
        return INT_MIN;
    }

    int getVertex(int index) {
        if (index >= 0 && index < length) {
            return vertexes[index];
        }
        return INT_MIN;
    }

    void clear() {
        vertexes.assign(capacity, 0);
        for (vector<int> &edge : edges) {
            edge.assign(capacity, 0);
        }
        length = 0;
    }

private:
    vector<int> vertexes;
    vector<vector<int>> edges;
    int length;
    int capacity;
};
