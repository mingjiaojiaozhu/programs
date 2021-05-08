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

class Gabow {
public:
    vector<vector<int>> search(vector<VertexNode *> &graphs) {
        vector<int> parent(graphs.size(), -1);
        vector<bool> visited(graphs.size(), false);
        stack<int> path;
        stack<int> root;

        vector<vector<int>> result(0);
        vector<int> aux(0);
        for (int i = 0; i < (int) graphs.size(); ++i) {
            if (!~parent[i]) {
                search(graphs, i, parent, visited, path, root, result, aux, 0);
            }
        }
        return result;
    }

private:
    int search(vector<VertexNode *> &graphs, int start, vector<int> &parent, vector<bool> &visited, stack<int> &path, stack<int> &root, vector<vector<int>> &result, vector<int> &aux, int count) {
        parent[start] = count;
        path.push(start);
        root.push(start);

        EdgeNode *edge = graphs[start]->next;
        while (edge) {
            int edgeIndex = edge->index;
            if (!~parent[edgeIndex]) {
                count = search(graphs, edgeIndex, parent, visited, path, root, result, aux, count + 1);
            } else if (!visited[edgeIndex]) {
                while (parent[root.top()] > parent[edgeIndex]) {
                    root.pop();
                }
            }
            edge = edge->next;
        }

        if (start != root.top()) {
            return count;
        }
        root.pop();

        int index = path.top();
        path.pop();
        while (index != start) {
            aux.emplace_back(index);
            visited[index] = true;
            index = path.top();
            path.pop();
        }
        aux.emplace_back(start);
        visited[start] = true;
        result.emplace_back(aux);
        aux.clear();
        return count;
    }
};
