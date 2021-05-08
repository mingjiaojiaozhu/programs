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

class Fleury {
public:
    vector<int> search(vector<VertexNode *> &graphs) {
        int start = getStart(graphs);
        if (!~start) {
            return vector<int>(0);
        }

        vector<vector<bool>> visited(graphs.size(), vector<bool>(graphs.size(), false));
        stack<int> stack;
        stack.push(start);

        vector<int> result(0);
        while (!stack.empty()) {
            int index = stack.top();
            stack.pop();
            EdgeNode *edge = graphs[index]->next;
            bool flag = false;
            while (edge) {
                int edgeIndex = edge->index;
                if (!visited[index][edgeIndex]) {
                    flag = true;
                    break;
                }
                edge = edge->next;
            }
            if (!flag) {
                result.emplace_back(index);
            } else {
                search(graphs, index, stack, visited);
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }

private:
    void search(vector<VertexNode *> &graphs, int start, stack<int> &stack, vector<vector<bool>> &visited) {
        stack.push(start);
        EdgeNode *edge = graphs[start]->next;
        while (edge) {
            int edgeIndex = edge->index;
            if (!visited[start][edgeIndex]) {
                visited[start][edgeIndex] = true;
                visited[edgeIndex][start] = true;
                search(graphs, edgeIndex, stack, visited);
                break;
            }
            edge = edge->next;
        }
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
