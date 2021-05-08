#include <iostream>
#include <vector>
using namespace std;

class ContinuousPostage {
public:
    vector<int> solution(int num, int count) {
        vector<int> result(num, 0);
        vector<int> aux(num + 1, 0);
        aux[1] = 1;
        vector<int> ends((num * count) << 6, INT_MAX);
        ends[0] = 0;
        search(num, count, 1, 1, ends, 0, aux, result);
        return result;
    }

private:
    int search(int num, int count, int start, int index, vector<int> &ends, int maxValue, vector<int> &aux, vector<int> &result) {
        for (int i = 0; i <= aux[start - 1] * (count - 1); ++i) {
            if (ends[i] < count) {
                for (int j = 1; j <= count - ends[i]; ++j) {
                    if (ends[i + aux[start] * j] > ends[i] + j) {
                        ends[i + aux[start] * j] = ends[i] + j;
                    }
                }
            }
        }
        while (ends[index] < INT_MAX) {
            ++index;
        }

        if (start == num) {
            if (maxValue < index - 1) {
                result.assign(aux.begin() + 1, aux.end());
                maxValue = index - 1;
            }
            return maxValue;
        }

        vector<int> pivot(ends.begin(), ends.end());
        for (int i = aux[start] + 1; i <= index; ++i) {
            if (ends[index - i] < count) {
                aux[start + 1] = i;
                maxValue = search(num, count, start + 1, index + 1, ends, maxValue, aux, result);
                ends.assign(pivot.begin(), pivot.end());
            }
        }
        return maxValue;
    }
};
