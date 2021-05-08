#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class KuhnMunkres {
public:
    vector<int> search(vector<vector<int>> &graphs) {
        vector<vector<int>> weights(3, vector<int>(0));
        weights[0].assign(graphs.size(), 0);
        for (int i = 0; i < (int) graphs.size(); ++i) {
            weights[1].emplace_back(*max_element(begin(graphs[i]), end(graphs[i])));
        }

        vector<int> result(graphs.size(), -1);
        for (int i = 0; i < (int) graphs.size(); ++i) {
            weights[2].assign(graphs.size(), INT_MAX);
            while (true) {
                vector<vector<bool>> visited(2, vector<bool>(graphs.size(), false));
                if (search(graphs, i, result, visited, weights)) {
                    break;
                }

                int weight = INT_MAX;
                for (int j = 0; j < (int) graphs.size(); ++j) {
                    if (!visited[0][j] && weight > weights[2][j]) {
                        weight = weights[2][j];
                    }
                }

                for (int j = 0; j < (int) graphs.size(); ++j) {
                    if (visited[1][j]) {
                        weights[1][j] -= weight;
                    }

                    if (visited[0][j]) {
                        weights[0][j] += weight;
                    } else {
                        weights[2][j] -= weight;
                    }
                }
            }
        }
        return result;
    }

private:
    bool search(vector<vector<int>> &graphs, int start, vector<int> &result, vector<vector<bool>> &visited, vector<vector<int>> &weights) {
        visited[1][start] = true;
        for (int i = 0; i < (int) graphs.size(); ++i) {
            if (visited[0][i]) {
                continue;
            }

            int weight = weights[1][start] + weights[0][i] - graphs[start][i];
            if (!weight) {
                visited[0][i] = true;
                if (!~result[i] || search(graphs, result[i], result, visited, weights)) {
                    result[i] = start;
                    return true;
                }
            } else {
                if (weights[2][i] > weight) {
                    weights[2][i] = weight;
                }
            }
        }
        return false;
    }
};
