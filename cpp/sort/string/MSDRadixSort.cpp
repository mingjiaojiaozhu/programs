#include <iostream>
#include <vector>
#include <string>
using namespace std;

class MSDRadixSort {
public:
    void sort(vector<string> &texts) {
        vector<string> aux(texts.size(), "");
        sort(texts, aux, 0, texts.size() - 1, 0);
    }

private:
    void sort(vector<string> &texts, vector<string> &aux, int start, int end, int digit) {
        if (start >= end) {
            return;
        }

        int maxValue = getChar(texts[start], digit);
        int minValue = getChar(texts[start], digit);
        for (int i = start + 1; i <= end; ++i) {
            int value = getChar(texts[i], digit);
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
        vector<int> buckets(size + 2, 0);
        for (int i = start; i <= end; ++i) {
            int value = getChar(texts[i], digit);
            ++buckets[!~value ? 1 : value - minValue + 2];
        }
        for (int i = 1; i < size + 2; ++i) {
            buckets[i] += buckets[i - 1];
        }

        for (int i = start; i <= end; ++i) {
            int value = getChar(texts[i], digit);
            int index = !~value ? 0 : value - minValue + 1;
            aux[buckets[index]] = texts[i];
            ++buckets[index];
        }
        copy(aux.begin(), aux.begin() + end - start + 1, texts.begin() + start);

        for (int i = 0; i < size; ++i) {
            sort(texts, aux, start + buckets[i], start + buckets[i + 1] - 1, digit + 1);
        }
    }

    int getChar(string text, int digit) {
        if ((int) text.length() <= digit) {
            return -1;
        }
        return text[digit];
    }
};
