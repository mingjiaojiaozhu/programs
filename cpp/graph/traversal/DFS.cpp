#include <iostream>
#include <vector>
#include <stack>
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

class DFS {
public:
    vector<int> traverse(vector<VertexNode *> &graphs, int start) {
        vector<bool> visited(graphs.size(), false);
        stack<int> stack;
        stack.push(start);

        vector<int> result(0);
        while (!stack.empty()) {
            int index = stack.top();
            stack.pop();
            if (visited[index]) {
                continue;
            }

            result.emplace_back(index);
            visited[index] = true;

            EdgeNode *edge = graphs[index]->next;
            while (edge) {
                int edgeIndex = edge->index;
                if (!visited[edgeIndex]) {
                    stack.push(edgeIndex);
                }
                edge = edge->next;
            }
        }
        return result;
    }
};
