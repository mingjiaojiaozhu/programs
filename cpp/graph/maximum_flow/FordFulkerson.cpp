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

class FordFulkerson {
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

        vector<int> parent(graphs.size(), -1);
        int result = 0;
        while (search(graphs, start, end, weights, parent)) {
            int value = INT_MAX;
            int index = end;
            while (index != start) {
                if (value > weights[parent[index]][index]) {
                    value = weights[parent[index]][index];
                }
                index = parent[index];
            }

            index = end;
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
    bool search(vector<VertexNode *> &graphs, int start, int end, vector<vector<int>> &weights, vector<int> &parent) {
        vector<bool> visited(graphs.size(), false);
        visited[start] = true;
        queue<int> queue;
        queue.push(start);
        while (!queue.empty()) {
            int index = queue.front();
            queue.pop();
            EdgeNode *edge = graphs[index]->next;
            while (edge) {
                int edgeIndex = edge->index;
                if (!visited[edgeIndex] && weights[index][edgeIndex]) {
                    parent[edgeIndex] = index;
                    visited[edgeIndex] = true;
                    queue.push(edgeIndex);
                }
                edge = edge->next;
            }
        }
        return visited[end];
    }
};
