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

class BFS {
public:
    vector<int> traverse(vector<VertexNode *> &graphs, int start) {
        vector<bool> visited(graphs.size(), false);
        visited[start] = true;
        queue<int> queue;
        queue.push(start);

        vector<int> result(0);
        result.emplace_back(start);
        while (!queue.empty()) {
            int index = queue.front();
            queue.pop();
            EdgeNode *edge = graphs[index]->next;
            while (edge) {
                int edgeIndex = edge->index;
                if (!visited[edgeIndex]) {
                    result.emplace_back(edgeIndex);
                    visited[edgeIndex] = true;
                    queue.push(edgeIndex);
                }
                edge = edge->next;
            }
        }
        return result;
    }
};
