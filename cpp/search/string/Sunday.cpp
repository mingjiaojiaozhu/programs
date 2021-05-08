#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Sunday {
public:
    int search(string text, string pattern) {
        int maxValue = *max_element(begin(text), end(text));
        int minValue = *min_element(begin(text), end(text));
        vector<int> next = getNext(pattern, maxValue - minValue + 1, minValue);

        int index = 0;
        while (index <= (int) text.size() - (int) pattern.size()) {
            int patternIndex = 0;
            while (text[index + patternIndex] == pattern[patternIndex]) {
                ++patternIndex;
                if (patternIndex == pattern.size()) {
                    return index;
                }
            }

            if (index == text.size() - pattern.size()) {
                return -1;
            }
            index += next[text[index + pattern.size()] - minValue];
        }
        return -1;
    }

private:
    vector<int> getNext(string text, int nextSize, int minValue) {
        vector<int> next(nextSize, text.size() + 1);
        for (int i = 0; i < (int) text.size(); ++i) {
            int index = text[i] - minValue;
            if (index >= 0 && index < nextSize) {
                next[index] = text.size() - i;
            }
        }
        return next;
    }
};
