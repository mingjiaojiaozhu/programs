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

class Dinic {
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

        vector<int> minCost(0);
        vector<bool> visited(graphs.size(), false);
        vector<int> result(2, 0);
        while (searchOfBFS(graphs, start, end, weights, minCost)) {
            visited[end] = true;
            while (visited[end]) {
                visited.assign(graphs.size(), false);
                searchOfDFS(graphs, start, end, INT_MAX, weights, minCost, visited, result);
            }
        }
        return result;
    }

private:
    bool searchOfBFS(vector<VertexNode *> &graphs, int start, int end, vector<vector<int>> &weights, vector<int> &minCost) {
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

    int searchOfDFS(vector<VertexNode *> &graphs, int start, int end, int flow, vector<vector<int>> &weights, vector<int> &minCost, vector<bool> &visited, vector<int> &result) {
        if (start == end) {
            visited[end] = true;
            result[0] += flow;
            return flow;
        }

        visited[start] = true;
        EdgeNode *edge = graphs[start]->next;
        int pivot = 0;
        while (edge) {
            int edgeIndex = edge->index;
            if ((!visited[edgeIndex] || edgeIndex == end) && weights[start][edgeIndex] && minCost[edgeIndex] == minCost[start] + edge->price) {
                int value = searchOfDFS(graphs, edgeIndex, end, min(flow - pivot, weights[start][edgeIndex]), weights, minCost, visited, result);
                if (value) {
                    pivot += value;
                    result[1] += value * edge->price;
                    weights[start][edgeIndex] -= value;
                    weights[edgeIndex][start] += value;
                    if (pivot == flow) {
                        break;
                    }
                }
            }
            edge = edge->next;
        }
        return pivot;
    }
};
