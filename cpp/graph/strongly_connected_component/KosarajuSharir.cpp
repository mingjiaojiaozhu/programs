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

class KosarajuSharir {
public:
    vector<vector<int>> search(vector<VertexNode *> &graphs) {
        vector<bool> visited(graphs.size(), false);
        stack<int> stack;
        search(graphs, 0, visited, stack);

        vector<VertexNode *> inverseGraphs(0);
        for (int i = 0; i < (int) graphs.size(); ++i) {
            inverseGraphs.emplace_back(new VertexNode(graphs[i]->value));
        }
        for (int i = graphs.size() - 1; i >= 0; --i) {
            EdgeNode *edge = graphs[i]->next;
            while (edge) {
                int edgeIndex = edge->index;
                EdgeNode *edgeNode = new EdgeNode(i, edge->weight);
                edgeNode->next = inverseGraphs[edgeIndex]->next;
                inverseGraphs[edgeIndex]->next = edgeNode;
                edge = edge->next;
            }
        }

        visited.assign(graphs.size(), false);
        vector<vector<int>> result(0);
        vector<int> aux(0);
        while (!stack.empty()) {
            int index = stack.top();
            stack.pop();
            if (!visited[index]) {
                reverseSearch(inverseGraphs, index, visited, aux);
                result.emplace_back(aux);
                aux.clear();
            }
        }
        return result;
    }

private:
    void search(vector<VertexNode *> &graphs, int start, vector<bool> &visited, stack<int> &stack) {
        visited[start] = true;
        EdgeNode *edge = graphs[start]->next;
        while (edge) {
            int edgeIndex = edge->index;
            if (!visited[edgeIndex]) {
                search(graphs, edgeIndex, visited, stack);
            }
            edge = edge->next;
        }
        stack.push(start);
    }

    void reverseSearch(vector<VertexNode *> &graphs, int start, vector<bool> &visited, vector<int> &aux) {
        visited[start] = true;
        aux.emplace_back(start);

        EdgeNode *edge = graphs[start]->next;
        while (edge) {
            int edgeIndex = edge->index;
            if (!visited[edgeIndex]) {
                reverseSearch(graphs, edgeIndex, visited, aux);
            }
            edge = edge->next;
        }
    }
};
