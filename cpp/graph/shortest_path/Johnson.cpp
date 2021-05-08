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

class Johnson {
public:
    vector<vector<int>> search(vector<VertexNode *> &graphs) {
        vector<VertexNode *> aux(graphs.size() + 1, nullptr);
        copy(graphs.begin(), graphs.end(), aux.begin());
        aux[graphs.size()] = new VertexNode(0);
        for (int i = graphs.size() - 1; i >= 0; --i) {
            EdgeNode *edge = new EdgeNode(i, 0);
            edge->next = aux[graphs.size()]->next;
            aux[graphs.size()]->next = edge;
        }

        vector<int> reWeight = bellmanFord(aux, graphs.size());
        if (reWeight.empty()) {
            return vector<vector<int>>(0);
        }

        for (int i = 0; i < (int) graphs.size(); ++i) {
            EdgeNode *edge = graphs[i]->next;
            while (edge) {
                edge->weight += reWeight[i] - reWeight[edge->index];
                edge = edge->next;
            }
        }

        vector<vector<int>> result(0);
        for (int i = 0; i < (int) graphs.size(); ++i) {
            result.emplace_back(dijkstra(graphs, i));
            for (int j = 0; j < (int) graphs.size(); ++j) {
                if (INT_MAX != result[i][j]) {
                    result[i][j] += reWeight[j] - reWeight[i];
                }
            }
        }
        return result;
    }

private:
    typedef struct HeapNode {
        int index;
        int weight;

        HeapNode(int index, int weight) : index(index), weight(weight) {}
    } HeapNode, *pNode;

    struct cmp {
        bool operator() (const pNode node1, const pNode node2) {
            return node1->weight > node2->weight;
        }
    };

    vector<int> bellmanFord(vector<VertexNode *> &graphs, int start) {
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

    vector<int> dijkstra(vector<VertexNode *> &graphs, int start) {
        vector<bool> visited(graphs.size(), false);
        priority_queue<pNode, vector<pNode>, cmp> queue;
        queue.push(new HeapNode(start, 0));

        vector<int> result(graphs.size(), INT_MAX);
        while (!queue.empty()) {
            HeapNode *heap = queue.top();
            queue.pop();
            int index = heap->index;
            int weight = heap->weight;
            if (visited[index]) {
                continue;
            }

            result[index] = weight;
            visited[index] = true;

            EdgeNode *edge = graphs[index]->next;
            while (edge) {
                int edgeIndex = edge->index;
                int edgeWeight = weight + edge->weight;
                if (!visited[edgeIndex]) {
                    queue.push(new HeapNode(edgeIndex, edgeWeight));
                }
                edge = edge->next;
            }
        }
        return result;
    }
};
