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

class BellmanFord {
public:
    vector<int> search(vector<VertexNode *> &graphs, int start) {
        vector<int> result(graphs.size(), INT_MAX);
        result[start] = 0;

        int index = start;
        for (VertexNode *_ : graphs) {
            EdgeNode *edge = graphs[index]->next;
            while (edge) {
                int pivot = result[index] + edge->weight;
                int edgeIndex = edge->index;
                if (INT_MAX != result[index] && pivot < result[edgeIndex]) {
                    result[edgeIndex] = pivot;
                }
                edge = edge->next;
            }

            ++index;
            if (index >= (int) graphs.size()) {
                index = 0;
            }
        }

        index = start;
        for (VertexNode *_ : graphs) {
            EdgeNode *edge = graphs[index]->next;
            while (edge) {
                int pivot = result[index] + edge->weight;
                int edgeIndex = edge->index;
                if (INT_MAX != result[index] && pivot < result[edgeIndex]) {
                    return vector<int>(0);
                }
                edge = edge->next;
            }

            ++index;
            if (index >= (int) graphs.size()) {
                index = 0;
            }
        }
        return result;
    }
};
