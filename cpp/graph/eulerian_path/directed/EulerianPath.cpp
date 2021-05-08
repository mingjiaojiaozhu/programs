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

class EulerianPath {
public:
    vector<int> search(vector<VertexNode *> &graphs) {
        int start = getStart(graphs);
        if (!~start) {
            return vector<int>(0);
        }

        vector<vector<bool>> visited(graphs.size(), vector<bool>(graphs.size(), false));
        vector<int> result(0);
        search(graphs, start, visited, result);
        result.emplace_back(start);
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
                search(graphs, edgeIndex, visited, result);
                result.emplace_back(edgeIndex);
            }
            edge = edge->next;
        }
    }

    int getStart(vector<VertexNode *> &graphs) {
        vector<int> inDegrees(graphs.size(), 0);
        vector<int> outDegrees(graphs.size(), 0);
        for (int i = 0; i < (int) graphs.size(); ++i) {
            EdgeNode *edge = graphs[i]->next;
            while (edge) {
                ++inDegrees[edge->index];
                ++outDegrees[i];
                edge = edge->next;
            }
        }

        int start = 0;
        int inCount = 0;
        int outCount = 0;
        for (int i = graphs.size() - 1; i >= 0; --i) {
            if (abs(inDegrees[i] - outDegrees[i]) > 1) {
                return -1;
            }

            if (1 == outDegrees[i] - inDegrees[i]) {
                start = i;
                ++inCount;
            } else if (1 == inDegrees[i] - outDegrees[i]) {
                ++outCount;
            }
            if (inCount > 1 || outCount > 1) {
                break;
            }
        }
        return ((!inCount && !outCount) || (1 == inCount && 1 == outCount)) ? start : -1;
    }
};
