#include <iostream>
#include <vector>
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

class TopologicalSort {
public:
    vector<int> sort(vector<VertexNode *> &graphs) {
        vector<vector<bool>> visited(2, vector<bool>(graphs.size(), false));
        vector<int> result(0);
        for (int i = 0; i < (int) graphs.size(); ++i) {
            if (!visited[0][i] && !search(graphs, i, result, visited)) {
                return vector<int>(0);
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }

private:
    bool search(vector<VertexNode *> &graphs, int start, vector<int> &result, vector<vector<bool>> &visited) {
        visited[1][start] = true;
        EdgeNode *edge = graphs[start]->next;
        while (edge) {
            int edgeIndex = edge->index;
            if (visited[1][edgeIndex] || (!visited[0][edgeIndex] && !search(graphs, edgeIndex, result, visited))) {
                return false;
            }
            edge = edge->next;
        }

        visited[0][start] = true;
        visited[1][start] = false;
        result.emplace_back(start);
        return true;
    }
};
