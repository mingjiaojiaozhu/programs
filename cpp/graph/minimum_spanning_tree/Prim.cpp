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

class Prim {
public:
    vector<int> search(vector<VertexNode *> &graphs, int start) {
        vector<bool> visited(graphs.size(), false);
        priority_queue<pNode, vector<pNode>, cmp> queue;
        queue.push(new HeapNode(-1, start, 0));

        vector<int> result(graphs.size(), -1);
        while (!queue.empty()) {
            HeapNode *heap = queue.top();
            queue.pop();
            int fromIndex = heap->fromIndex;
            int toIndex = heap->toIndex;
            if (visited[toIndex]) {
                continue;
            }

            result[toIndex] = fromIndex;
            visited[toIndex] = true;

            EdgeNode *edge = graphs[toIndex]->next;
            while (edge) {
                int edgeIndex = edge->index;
                int edgeWeight = edge->weight;
                if (!visited[edgeIndex]) {
                    queue.push(new HeapNode(toIndex, edgeIndex, edgeWeight));
                }
                edge = edge->next;
            }
        }
        return result;
    }

private:
    typedef struct HeapNode {
        int fromIndex;
        int toIndex;
        int weight;

        HeapNode(int fromIndex, int toIndex, int weight) : fromIndex(fromIndex), toIndex(toIndex), weight(weight) {}
    } HeapNode, *pNode;

    struct cmp {
        bool operator() (const pNode node1, const pNode node2) {
            return node1->weight > node2->weight;
        }
    };
};
