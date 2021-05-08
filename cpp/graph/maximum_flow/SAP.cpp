#include <iostream>
#include <vector>
using namespace std;

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

class SAP {
public:
    int search(vector<VertexNode *> &graphs, int start, int end) {
        vector<vector<int>> weights(graphs.size(), vector<int>(graphs.size(), 0));
        for (int i = 0; i < (int) graphs.size(); ++i) {
            EdgeNode *edge = graphs[i]->next;
            while (edge) {
                weights[i][edge->index] = edge->weight;
                edge = edge->next;
            }
        }

        vector<int> gap(graphs.size() + 1, 0);
        gap[0] = graphs.size();
        vector<int> degrees(graphs.size(), 0);
        int result = 0;
        while (degrees[start] != graphs.size()) {
            result += search(graphs, start, end, start, INT_MAX, weights, gap, degrees);
        }
        return result;
    }

private:
    int search(vector<VertexNode *> &graphs, int start, int end, int index, int flow, vector<vector<int>> &weights, vector<int> &gap, vector<int> &degrees) {
        if (index == end) {
            return flow;
        }

        EdgeNode *edge = graphs[index]->next;
        int pivot = flow;
        int border = graphs.size() - 1;
        while (edge) {
            int edgeIndex = edge->index;
            if (weights[index][edgeIndex]) {
                if (degrees[index] == degrees[edgeIndex] + 1) {
                    int value = search(graphs, start, end, edgeIndex, min(pivot, weights[index][edgeIndex]), weights, gap, degrees);
                    weights[index][edgeIndex] -= value;
                    weights[edgeIndex][index] += value;
                    pivot -= value;
                    if (degrees[start] == graphs.size() || !pivot) {
                        return flow - pivot;
                    }
                }
                if (border > degrees[edgeIndex]) {
                    border = degrees[edgeIndex];
                }
            }
            edge = edge->next;
        }

        --gap[degrees[index]];
        if (!~gap[degrees[index]]) {
            degrees[start] = graphs.size();
        } else {
            degrees[index] = border + 1;
            ++gap[degrees[index]];
        }
        return flow - pivot;
    }
};
