#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class BoyerMoore {
public:
    int search(string text, string pattern) {
        int maxValue = *max_element(begin(text), end(text));
        int minValue = *min_element(begin(text), end(text));
        vector<int> nextBadChar = getNextBadChar(pattern, maxValue - minValue + 1, minValue);
        vector<int> nextGoodSuffix = getNextGoodSuffix(pattern);

        int index = 0;
        while (index <= (int) text.size() - (int) pattern.size()) {
            int patternIndex = pattern.size() - 1;
            while (text[index + patternIndex] == pattern[patternIndex]) {
                --patternIndex;
                if (patternIndex < 0) {
                    return index;
                }
            }
            index += max(patternIndex - nextBadChar[text[index + patternIndex] - minValue], nextGoodSuffix[patternIndex]);
        }
        return -1;
    }

private:
    vector<int> getNextBadChar(string text, int nextSize, int minValue) {
        vector<int> next(nextSize, 0);
        for (int i = 0; i < (int) text.size(); ++i) {
            int index = text[i] - minValue;
            if (index >= 0 && index < nextSize) {
                next[index] = i;
            }
        }
        return next;
    }

    vector<int> getNextGoodSuffix(string text) {
        vector<int> aux(text.size(), 0);
        aux[text.size() - 1] = text.size();

        int start = 0;
        int end = text.size() - 1;
        for (int i = text.size() - 2; i >= 0; --i) {
            if (i > end && aux[i + text.size() - 1 - start] < i - end) {
                aux[i] = aux[i + text.size() - 1 - start];
                continue;
            }

            start = i;
            if (i < end) {
                end = i;
            }
            while (end >= 0 && text[end] == text[end + text.size() - 1 - start]) {
                --end;
                aux[i] = start - end;
            }
        }

        vector<int> next(text.size(), text.size());
        for (int i = text.size() - 1; i >= 0; --i) {
            if (aux[i] != i + 1) {
                continue;
            }

            for (int j = 0; j < (int) text.size() - i; ++j) {
                if (next[j] == text.size()) {
                    next[j] = text.size() - i - 1;
                }
            }
        }

        for (int i = 0; i < (int) text.size() - 1; ++i) {
            next[text.size() - 1 - aux[i]] = text.size() - i - 1;
        }
        return next;
    }
};
