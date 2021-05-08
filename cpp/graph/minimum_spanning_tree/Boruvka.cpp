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

class Boruvka {
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

        UnionFind *unionFind = new UnionFind(graphs.size());
        vector<int> result(graphs.size(), -1);
        while (true) {
            vector<ConnectedNode *> minEdges(graphs.size(), nullptr);
            bool flag = false;
            for (ConnectedNode *edge : edgeLists) {
                int fromIndex = unionFind->values[edge->fromIndex];
                int toIndex = unionFind->values[edge->toIndex];
                if (fromIndex != toIndex && (!minEdges[toIndex] || edge->weight < minEdges[toIndex]->weight)) {
                    minEdges[toIndex] = edge;
                    flag = true;
                }
            }

            if (!flag) {
                break;
            }

            for (ConnectedNode *edge : minEdges) {
                if (edge) {
                    int fromIndex = edge->fromIndex;
                    int toIndex = edge->toIndex;
                    if (unionFind->get(fromIndex) != unionFind->get(toIndex)) {
                        unionFind->add(fromIndex, toIndex);
                        result[toIndex] = fromIndex;
                    }
                }
            }
        }
        return result;
    }

private:
    struct ConnectedNode {
        int fromIndex;
        int toIndex;
        int weight;

        ConnectedNode(int fromIndex, int toIndex, int weight) : fromIndex(fromIndex), toIndex(toIndex), weight(weight) {}
    };

    struct UnionFind {
        vector<int> values;
        vector<int> weights;

        UnionFind(int degree) {
            for (int i = 0; i < degree; ++i) {
                values.emplace_back(i);
            }
            weights.assign(degree, 1);
        }

        void add(int num1, int num2) {
            int root1 = get(num1);
            int root2 = get(num2);
            if (root1 != root2) {
                if (weights[root1] < weights[root2]) {
                    values[root2] = root1;
                    weights[root1] += weights[root2];
                } else {
                    values[root1] = root2;
                    weights[root2] += weights[root1];
                }
            }
        }

        int get(int num) {
            int root = num;
            while (root != values[root]) {
                root = values[root];
            }

            while (num != root) {
                int aux = values[num];
                values[num] = root;
                num = aux;
            }
            return root;
        }
    };
};
