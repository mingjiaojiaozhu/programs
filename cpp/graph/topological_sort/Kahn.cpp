#include <iostream>
#include <vector>
#include <queue>
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

class Kahn {
public:
    vector<int> sort(vector<VertexNode *> &graphs) {
        vector<int> inDegrees(graphs.size(), 0);
        for (VertexNode *graph : graphs) {
            EdgeNode *edge = graph->next;
            while (edge) {
                ++inDegrees[edge->index];
                edge = edge->next;
            }
        }

        queue<int> queue;
        for (int i = 0; i < (int) graphs.size(); ++i) {
            if (!inDegrees[i]) {
                queue.push(i);
            }
        }

        vector<int> result(0);
        while (!queue.empty()) {
            int index = queue.front();
            queue.pop();
            result.emplace_back(index);

            EdgeNode *edge = graphs[index]->next;
            while (edge) {
                int edgeIndex = edge->index;
                --inDegrees[edgeIndex];
                if (!inDegrees[edgeIndex]) {
                    queue.push(edgeIndex);
                }
                edge = edge->next;
            }
        }
        return (result.size() == graphs.size()) ? result : vector<int>(0);
    }
};
