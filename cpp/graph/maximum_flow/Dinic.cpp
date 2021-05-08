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

class Dinic {
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
        int result = 0;
        while (searchOfBFS(graphs, start, end, weights, parent)) {
            result += searchOfDFS(graphs, start, end, INT_MAX, weights, parent);
        }
        return result;
    }

private:
    bool searchOfBFS(vector<VertexNode *> &graphs, int start, int end, vector<vector<int>> &weights, vector<int> &parent) {
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
                    queue.push(edgeIndex);
                }
                edge = edge->next;
            }
        }
        return 0 != ~parent[end];
    }

    int searchOfDFS(vector<VertexNode *> &graphs, int start, int end, int flow, vector<vector<int>> &weights, vector<int> &parent) {
        if (start == end) {
            return flow;
        }

        EdgeNode *edge = graphs[start]->next;
        while (edge) {
            int edgeIndex = edge->index;
            if (weights[start][edgeIndex] && parent[edgeIndex] == start) {
                int value = searchOfDFS(graphs, edgeIndex, end, min(flow, weights[start][edgeIndex]), weights, parent);
                if (value) {
                    weights[start][edgeIndex] -= value;
                    weights[edgeIndex][start] += value;
                    return value;
                }
            }
            edge = edge->next;
        }
        return 0;
    }
};
