#include <iostream>
#include <vector>
#include <stack>
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

class CriticalPath {
public:
    vector<int> search(vector<VertexNode *> &graphs) {
        stack<int> stack;
        vector<int> vertexEnd = topologicalSort(graphs, stack);
        if (vertexEnd.empty()) {
            return vector<int>(0);
        }
        vector<int> vertexLatest = reverseTopologicalSort(graphs, vertexEnd, stack);

        vector<int> result(0);
        for (int i = 0; i < (int) graphs.size(); ++i) {
            if (vertexEnd[i] == vertexLatest[i]) {
                result.emplace_back(i);
            }
        }
        return result;
    }

private:
    vector<int> topologicalSort(vector<VertexNode *> &graphs, stack<int> &stack) {
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

        vector<int> vertexEnd(graphs.size(), 0);
        int count = 0;
        while (!queue.empty()) {
            int index = queue.front();
            queue.pop();
            stack.push(index);
            ++count;

            EdgeNode *edge = graphs[index]->next;
            int pivot = vertexEnd[index];
            while (edge) {
                int edgeIndex = edge->index;
                int edgeWeight = edge->weight;
                --inDegrees[edgeIndex];
                if (!inDegrees[edgeIndex]) {
                    queue.push(edgeIndex);
                    if (vertexEnd[edgeIndex] < pivot + edgeWeight) {
                        vertexEnd[edgeIndex] = pivot + edgeWeight;
                    }
                }
                edge = edge->next;
            }
        }
        return (count == graphs.size()) ? vertexEnd : vector<int>(0);
    }

    vector<int> reverseTopologicalSort(vector<VertexNode *> &graphs, vector<int> &vertexEnd, stack<int> &stack) {
        int maxValue = vertexEnd[stack.top()];
        stack.pop();
        vector<int> vertexLatest(graphs.size(), maxValue);
        while (!stack.empty()) {
            int index = stack.top();
            stack.pop();
            EdgeNode *edge = graphs[index]->next;
            while (edge) {
                int edgeIndex = edge->index;
                int edgeWeight = edge->weight;
                if (vertexLatest[index] > vertexLatest[edgeIndex] - edgeWeight) {
                    vertexLatest[index] = vertexLatest[edgeIndex] - edgeWeight;
                }
                edge = edge->next;
            }
        }
        return vertexLatest;
    }
};
