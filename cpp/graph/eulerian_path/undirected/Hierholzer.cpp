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

class Hierholzer {
public:
    vector<int> search(vector<VertexNode *> &graphs) {
        int start = getStart(graphs);
        if (!~start) {
            return vector<int>(0);
        }

        vector<vector<bool>> visited(graphs.size(), vector<bool>(graphs.size(), false));
        vector<int> result(0);
        search(graphs, start, visited, result);
        reverse(result.begin(), result.end());
        return result;
    }

private:
    void search(vector<VertexNode *> &graphs, int start, vector<vector<bool>> &visited, vector<int> &result) {
        EdgeNode *edge = graphs[start]->next;
        while (edge) {
            int edgeIndex = edge->index;
            if (!visited[start][edgeIndex]) {
                visited[start][edgeIndex] = true;
                visited[edgeIndex][start] = true;
                search(graphs, edgeIndex, visited, result);
            }
            edge = edge->next;
        }
        result.emplace_back(start);
    }

    int getStart(vector<VertexNode *> &graphs) {
        int start = 0;
        int oddCount = 0;
        for (int i = graphs.size() - 1; i >= 0; --i) {
            int count = 0;
            EdgeNode *edge = graphs[i]->next;
            while (edge) {
                ++count;
                edge = edge->next;
            }
            if (count & 1) {
                start = i;
                ++oddCount;
            }
        }
        return (!oddCount || 2 == oddCount) ? start : -1;
    }
};
