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

class Dijkstra {
public:
    vector<int> search(vector<VertexNode *> &graphs, int start) {
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
};
