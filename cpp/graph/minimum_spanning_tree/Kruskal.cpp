#include <iostream>
#include <vector>
#include <algorithm>
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

class Kruskal {
public:
    vector<int> search(vector<VertexNode *> &graphs) {
        vector<ConnectedNode *> edgeLists(0);
        for (int i = 0; i < (int) graphs.size(); ++i) {
            EdgeNode *edge = graphs[i]->next;
            while (edge) {
                edgeLists.emplace_back(new ConnectedNode(i, edge->index, edge->weight));
                edge = edge->next;
            }
        }

        sort(edgeLists.begin(), edgeLists.end(), cmp);

        vector<int> roots(graphs.size(), -1);
        vector<bool> visited(graphs.size(), false);

        vector<int> result(graphs.size(), -1);
        for (ConnectedNode *edge : edgeLists) {
            int fromIndex = edge->fromIndex;
            int toIndex = edge->toIndex;
            if (!visited[toIndex] && getRoot(roots, fromIndex) != getRoot(roots, toIndex)) {
                result[toIndex] = fromIndex;
                roots[fromIndex] = toIndex;
                visited[toIndex] = true;
            }
        }
        return result;
    }

private:
    typedef struct ConnectedNode {
        int fromIndex;
        int toIndex;
        int weight;

        ConnectedNode(int fromIndex, int toIndex, int weight) : fromIndex(fromIndex), toIndex(toIndex), weight(weight) {}
    } ConnectedNode, *pNode;

    int getRoot(vector<int> &roots, int index) {
        while (~roots[index]) {
            index = roots[index];
        }
        return index;
    }

    static bool cmp(const pNode &node1, const pNode &node2) {
        return node1->weight < node2->weight;
    }
};
