#include <iostream>
#include <vector>
using namespace std;

class Hungary {
public:
    vector<int> search(vector<vector<int>> &graphs) {
        vector<int> result(graphs.size(), -1);
        for (int i = 0; i < (int) graphs.size(); ++i) {
            vector<bool> visited(graphs.size(), false);
            if (!search(graphs, i, result, visited)) {
                return vector<int>(0);
            }
        }
        return result;
    }

private:
    bool search(vector<vector<int>> &graphs, int start, vector<int> &result, vector<bool> &visited) {
        for (int i = 0; i < (int) graphs.size(); ++i) {
            if (graphs[i][start] && !visited[i]) {
                visited[i] = true;
                if (!~result[i] || search(graphs, result[i], result, visited)) {
                    result[i] = start;
                    return true;
                }
            }
        }
        return false;
    }
};
