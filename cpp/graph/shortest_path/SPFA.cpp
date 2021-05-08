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

class SPFA {
public:
    vector<int> search(vector<VertexNode *> &graphs, int start) {
        vector<bool> visited(graphs.size(), false);
        queue<int> queue;
        queue.push(start);

        vector<int> result(graphs.size(), INT_MAX);
        result[start] = 0;

        int count = 0;
        while (!queue.empty()) {
            int index = queue.front();
            queue.pop();
            visited[index] = false;

            EdgeNode *edge = graphs[index]->next;
            while (edge) {
                int edgeIndex = edge->index;
                int edgeWeight = edge->weight;
                if (result[edgeIndex] > result[index] + edgeWeight) {
                    result[edgeIndex] = result[index] + edgeWeight;
                    if (!visited[edgeIndex]) {
                        queue.push(edgeIndex);
                        visited[edgeIndex] = true;
                        ++count;
                    }
                }
                edge = edge->next;
            }
            if (count >= (int) graphs.size()) {
                return vector<int>(0);
            }
        }
        return result;
    }
};
