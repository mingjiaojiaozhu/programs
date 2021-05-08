#include <iostream>
#include <vector>
#include <string>
using namespace std;

class LSDRadixSort {
public:
    void sort(vector<string> &texts) {
        vector<string> aux(texts.size(), "");
        for (int i = texts[0].length() - 1; i >= 0; --i) {
            int maxValue = texts[0][i];
            int minValue = texts[0][i];
            for (int j = 1; j < (int) texts.size(); ++j) {
                int value = texts[j][i];
                if (!~value) {
                    continue;
                }

                if (maxValue < value) {
                    maxValue = value;
                }
                if (!~minValue || minValue > value) {
                    minValue = value;
                }
            }

            int size = maxValue - minValue + 1;
            vector<int> buckets(size, 0);
            for (string value : texts) {
                ++buckets[value[i] - minValue];
            }
            for (int j = 1; j < size; ++j) {
                buckets[j] += buckets[j - 1];
            }

            for (int j = texts.size() - 1; j >= 0; --j) {
                int index = texts[j][i] - minValue;
                aux[buckets[index] - 1] = texts[j];
                --buckets[index];
            }
            texts.assign(aux.begin(), aux.end());
        }
    }
};
