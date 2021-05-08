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

class Tarjan {
public:
    vector<vector<int>> search(vector<VertexNode *> &graphs) {
        vector<int> parent(graphs.size(), -1);
        stack<int> stack;

        vector<vector<int>> result(0);
        vector<int> aux(0);
        for (int i = 0; i < (int) graphs.size(); ++i) {
            if (!~parent[i]) {
                search(graphs, i, parent, stack, result, aux, 0);
            }
        }
        return result;
    }

private:
    int search(vector<VertexNode *> &graphs, int start, vector<int> &parent, stack<int> &stack, vector<vector<int>> &result, vector<int> &aux, int count) {
        parent[start] = count;
        int minValue = count;
        stack.push(start);

        EdgeNode *edge = graphs[start]->next;
        while (edge) {
            int edgeIndex = edge->index;
            if (!~parent[edgeIndex]) {
                count = search(graphs, edgeIndex, parent, stack, result, aux, count + 1);
            }
            edge = edge->next;

            if (minValue > parent[edgeIndex]) {
                minValue = parent[edgeIndex];
            }
        }

        if (parent[start] > minValue) {
            parent[start] = minValue;
            return count;
        }

        int index = stack.top();
        stack.pop();
        while (index != start) {
            aux.emplace_back(index);
            parent[index] = INT_MAX;
            index = stack.top();
            stack.pop();
        }
        aux.emplace_back(start);
        parent[start] = INT_MAX;
        result.emplace_back(aux);
        aux.clear();
        return count;
    }
};
