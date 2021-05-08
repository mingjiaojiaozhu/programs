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

class EdmondsKarp {
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

        vector<int> parent(0);
        vector<int> maxFlow(graphs.size(), INT_MAX);
        int result = 0;
        while (true) {
            int value = search(graphs, start, end, weights, parent, maxFlow);
            if (!~value) {
                break;
            }

            int index = end;
            while (index != start) {
                weights[parent[index]][index] -= value;
                weights[index][parent[index]] += value;
                index = parent[index];
            }
            result += value;
        }
        return result;
    }

private:
    int search(vector<VertexNode *> &graphs, int start, int end, vector<vector<int>> &weights, vector<int> &parent, vector<int> &maxFlow) {
        parent.assign(graphs.size(), -1);
        queue<int> queue;
        queue.push(start);
        while (!queue.empty()) {
            int index = queue.front();
            queue.pop();
            EdgeNode *edge = graphs[index]->next;
            while (edge) {
                int edgeIndex = edge->index;
                if (weights[index][edgeIndex] && !~parent[edgeIndex]) {
                    parent[edgeIndex] = index;
                    maxFlow[edgeIndex] = min(weights[index][edgeIndex], maxFlow[index]);
                    queue.push(edgeIndex);
                }
                edge = edge->next;
            }
        }
        return ~parent[end] ? maxFlow[end] : -1;
    }
};
