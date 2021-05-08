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

class HLPP {
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

        vector<int> gap(graphs.size(), 0);
        vector<int> degrees(graphs.size(), 0);
        degrees[start] = graphs.size();
        priority_queue<pNode, vector<pNode>, cmp> queue;
        vector<int> result(graphs.size(), 0);
        result[start] = INT_MAX;

        EdgeNode *edge = graphs[start]->next;
        while (edge) {
            int edgeIndex = edge->index;
            int value = min(result[start], weights[start][edgeIndex]);
            weights[start][edgeIndex] -= value;
            weights[edgeIndex][start] += value;
            result[start] -= value;
            result[edgeIndex] += value;
            if (value && edgeIndex != end) {
                queue.push(new HeapNode(edgeIndex, degrees[edgeIndex]));
            }
            edge = edge->next;
        }

        while (!queue.empty()) {
            HeapNode *heap = queue.top();
            queue.pop();
            int index = heap->index;
            if (result[index]) {
                search(graphs, index, end, weights, gap, degrees, queue, result);
            }
        }
        return result[end];
    }

private:
    typedef struct HeapNode {
        int index;
        int degree;

        HeapNode(int index, int degree) : index(index), degree(degree) {}
    } HeapNode, *pNode;

    struct cmp {
        bool operator() (const pNode node1, const pNode node2) {
            return node1->degree < node2->degree;
        }
    };

    void search(vector<VertexNode *> &graphs, int start, int end, vector<vector<int>> &weights, vector<int> &gap, vector<int> &degrees, priority_queue<pNode, vector<pNode>, cmp> &queue, vector<int> &result) {
        EdgeNode *edge = graphs[start]->next;
        while (edge) {
            int edgeIndex = edge->index;
            if (degrees[start] == degrees[edgeIndex] + 1) {
                int value = min(result[start], weights[start][edgeIndex]);
                weights[start][edgeIndex] -= value;
                weights[edgeIndex][start] += value;
                result[start] -= value;
                result[edgeIndex] += value;
                if (value && edgeIndex != end) {
                    queue.push(new HeapNode(edgeIndex, degrees[edgeIndex]));
                }
            }
            edge = edge->next;
        }

        if (start != end && result[start]) {
            --gap[degrees[start]];
            if (!~gap[degrees[start]]) {
                for (int i = 0;i < (int) graphs.size(); ++i) {
                    if (i != end && degrees[i] > degrees[start] && degrees[i] < (int) graphs.size()) {
                        degrees[i]= graphs.size();
                    }
                }
            }
            ++degrees[start];
            if (degrees[start] < (int) graphs.size()) {
                ++gap[degrees[start]];
                queue.push(new HeapNode(start, degrees[start]));
            }
        }
    }
};
