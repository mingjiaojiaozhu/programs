#include <iostream>
#include <vector>
using namespace std;

class BatchJobsScheduling {
public:
    vector<int> solution(vector<vector<int>> &values) {
        vector<int> result(0);
        vector<int> aux(0);
        for (int i = 0; i < (int) values.size(); ++i) {
            aux.emplace_back(i);
        }
        vector<int> ends(3, 0);
        search(values, 0, ends, INT_MAX, aux, result);
        return result;
    }

private:
    int search(vector<vector<int>> &values, int start, vector<int> &ends, int minValue, vector<int> &aux, vector<int> &result) {
        if (start == values.size()) {
            result.assign(aux.begin(), aux.end());
            return ends[2];
        }

        for (int i = start; i < (int) values.size(); ++i) {
            ends[0] += values[aux[i]][0];
            int pivot = ends[1];
            ends[1] = max(ends[0], ends[1]) + values[aux[i]][1];
            ends[2] += ends[1];
            if (ends[2] < minValue) {
                swap(aux[start], aux[i]);
                minValue = search(values, start + 1, ends, minValue, aux, result);
                swap(aux[start], aux[i]);
            }
            ends[0] -= values[aux[i]][0];
            ends[2] -= ends[1];
            ends[1] = pivot;
        }
        return minValue;
    }
};
