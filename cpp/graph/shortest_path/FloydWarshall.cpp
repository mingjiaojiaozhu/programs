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

class FloydWarshall {
public:
    vector<vector<int>> search(vector<VertexNode *> &graphs) {
        vector<vector<int>> result(graphs.size(), vector<int>(graphs.size(), INT_MAX));
        for (int i = 0; i < (int) graphs.size(); ++i) {
            EdgeNode *edge = graphs[i]->next;
            while (edge) {
                result[i][edge->index] = edge->weight;
                edge = edge->next;
            }
            result[i][i] = 0;
        }

        for (int i = 0; i < (int) graphs.size(); ++i) {
            for (int j = 0; j < (int) graphs.size(); ++j) {
                for (int k = 0; k < (int) graphs.size(); ++k) {
                    if (INT_MAX == result[j][i] || INT_MAX == result[i][k]) {
                        continue;
                    }

                    int pivot = result[j][i] + result[i][k];
                    if (pivot < result[j][k]) {
                        result[j][k] = pivot;
                    }
                }
            }
        }
        return result;
    }
};
