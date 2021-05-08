#include <iostream>
#include <vector>
using namespace std;

class GraphOfAdjacencyList {
public:
    GraphOfAdjacencyList() : graphs(vector<VertexNode *>(64, nullptr)), length(0), capacity(64) {}

    bool isEmpty() {
        return !length;
    }

    void addEdge(int index, int edgeIndex, int weight) {
        if (index < 0 || index >= length || edgeIndex < 0 || edgeIndex >= length || index == edgeIndex) {
            return;
        }

        if (!graphs[index]->next) {
            graphs[index]->next = new EdgeNode(edgeIndex, weight);
            return;
        }

        EdgeNode *edge = graphs[index]->next;
        while (edge->next) {
            if (edgeIndex == edge->index) {
                edge->weight = weight;
                return;
            }
            edge = edge->next;
        }
        if (edgeIndex == edge->index) {
            edge->weight = weight;
        } else {
            edge->next = new EdgeNode(edgeIndex, weight);
        }
    }

    void addVertex(int value) {
        if (length >= capacity) {
            graphs.resize(capacity + 16, nullptr);
            capacity += 16;
        }

        graphs[length] = new VertexNode(value);
        ++length;
    }

    void eraseEdge(int index, int edgeIndex) {
        if (index < 0 || index >= length || edgeIndex < 0 || edgeIndex >= length || index == edgeIndex) {
            return;
        }

        EdgeNode *edge = graphs[index]->next;
        if (!edge) {
            return;
        }
        if (edgeIndex == edge->index) {
            graphs[index]->next = edge->next;
            return;
        }

        while (edge->next) {
            if (edgeIndex == edge->next->index) {
                edge->next = edge->next->next;
                return;
            }
            edge = edge->next;
        }
    }

    void eraseVertex(int index) {
        if (index < 0 || index >= length) {
            return;
        }

        for (int i = 0; i < length; ++i) {
            if (i != index) {
                eraseEdge(i, index);
            }
        }

        for (int i = index + 1; i < length; ++i) {
            graphs[i - 1] = graphs[i];
        }
        --length;
        graphs[length] = nullptr;
    }

    void setEdge(int index, int edgeIndex, int weight) {
        if (index < 0 || index >= length || edgeIndex < 0 || edgeIndex >= length || index == edgeIndex) {
            return;
        }

        EdgeNode *edge = graphs[index]->next;
        while (edge && edgeIndex != edge->index) {
            edge = edge->next;
        }

        if (edge) {
            edge->weight = weight;
        }
    }

    void setVertex(int index, int value) {
        if (index >= 0 && index < length) {
            graphs[index]->value = value;
        }
    }

    int getEdge(int index, int edgeIndex) {
        if (index < 0 || index >= length || edgeIndex < 0 || edgeIndex >= length || index == edgeIndex) {
            return INT_MIN;
        }

        EdgeNode *edge = graphs[index]->next;
        while (edge && edgeIndex != edge->index) {
            edge = edge->next;
        }

        if (edge) {
            return edge->weight;
        }
        return INT_MIN;
    }

    int getVertex(int index) {
        if (index >= 0 && index < length) {
            return graphs[index]->value;
        }
        return INT_MIN;
    }

    void clear() {
        graphs.assign(capacity, nullptr);
        length = 0;
    }

private:
    struct EdgeNode {
        int index;
        int weight;
        EdgeNode *next;

        EdgeNode(int index, int weight) : index(index), weight(weight), next(nullptr) {}
    };

    struct VertexNode {
        int value;
        EdgeNode *next;

        VertexNode(int value) : value(value), next(nullptr) {}
    };

    vector<VertexNode *> graphs;
    int length;
    int capacity;
};
