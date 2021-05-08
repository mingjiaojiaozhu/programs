#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct EdgeNode {
    int index;
    int weight;
    int price;
    EdgeNode *next;

    EdgeNode(int index, int weight, int price) : index(index), weight(weight), price(price), next(nullptr) {}
};

struct VertexNode {
    int value;
    EdgeNode *next;

    VertexNode(int value) : value(value), next(nullptr) {}
};

class SPFA {
public:
    vector<int> search(vector<VertexNode *> &graphs, int start, int end) {
        vector<vector<int>> weights(graphs.size(), vector<int>(graphs.size(), 0));
        for (int i = 0; i < (int) graphs.size(); ++i) {
            EdgeNode *edge = graphs[i]->next;
            while (edge) {
                weights[i][edge->index] = edge->weight;
                edge = edge->next;
            }
        }

        vector<int> parent(0);
        vector<int> maxFlow(0);
        vector<int> minCost(0);
        vector<int> result(2, 0);
        while (search(graphs, start, end, weights, parent, maxFlow, minCost)) {
            result[0] += maxFlow[end];
            result[1] += maxFlow[end] * minCost[end];

            int index = end;
            while (index != start) {
                weights[parent[index]][index] -= maxFlow[end];
                weights[index][parent[index]] += maxFlow[end];
                index = parent[index];
            }
        }
        return result;
    }

private:
    bool search(vector<VertexNode *> &graphs, int start, int end, vector<vector<int>> &weights, vector<int> &parent, vector<int> &maxFlow, vector<int> &minCost) {
        parent.assign(graphs.size(), -1);
        maxFlow.assign(graphs.size(), INT_MAX);
        minCost.assign(graphs.size(), INT_MAX);
        minCost[start] = 0;

        vector<bool> visited(graphs.size(), false);
        visited[start] = true;
        queue<int> queue;
        queue.push(start);
        while (!queue.empty()) {
            int index = queue.front();
            queue.pop();
            visited[index] = false;
            EdgeNode *edge = graphs[index]->next;
            while (edge) {
                int edgeIndex = edge->index;
                if (weights[index][edgeIndex] && minCost[edgeIndex] > minCost[index] + edge->price) {
                    parent[edgeIndex] = index;
                    maxFlow[edgeIndex] = min(maxFlow[index], weights[index][edgeIndex]);
                    minCost[edgeIndex] = minCost[index] + edge->price;
                    if (!visited[edgeIndex]) {
                        visited[edgeIndex] = true;
                        queue.push(edgeIndex);
                    }
                }
                edge = edge->next;
            }
        }
        return INT_MAX != minCost[end];
    }
};
