#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Horspool {
public:
    int search(string text, string pattern) {
        int maxValue = *max_element(begin(text), end(text));
        int minValue = *min_element(begin(text), end(text));
        vector<int> next = getNext(pattern, maxValue - minValue + 1, minValue);

        int index = 0;
        while (index <= (int) text.size() - (int) pattern.size()) {
            int patternIndex = pattern.size() - 1;
            while (text[index + patternIndex] == pattern[patternIndex]) {
                --patternIndex;
                if (patternIndex < 0) {
                    return index;
                }
            }
            index += next[text[index + pattern.size() - 1] - minValue];
        }
        return -1;
    }

private:
    vector<int> getNext(string text, int nextSize, int minValue) {
        vector<int> next(nextSize, text.size());
        for (int i = 0; i < (int) text.size() - 1; ++i) {
            int index = text[i] - minValue;
            if (index >= 0 && index < nextSize) {
                next[index] = text.size() - i - 1;
            }
        }
        return next;
    }
};
