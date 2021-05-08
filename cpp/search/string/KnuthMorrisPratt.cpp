#include <iostream>
#include <vector>
#include <string>
using namespace std;

class KnuthMorrisPratt {
public:
    int search(string text, string pattern) {
        vector<int> next = getNext(pattern);

        int index = 0;
        int patternIndex = 0;
        while (index < (int) text.size()) {
            if (patternIndex > 0 && text[index] != pattern[patternIndex]) {
                ++index;
                patternIndex = next[patternIndex - 1];
                continue;
            }

            if (patternIndex == pattern.size() - 1) {
                return index - patternIndex;
            }
            ++index;
            ++patternIndex;
        }
        return -1;
    }

private:
    vector<int> getNext(string text) {
        vector<int> next(text.size(), 0);

        int fast = 1;
        int slow = 0;
        while (fast < (int) text.size()) {
            if (slow && text[fast] != text[slow]) {
                slow = next[slow - 1];
                continue;
            }

            if (text[fast] == text[slow]) {
                ++slow;
            }
            next[fast] = slow;
            ++fast;
        }
        return next;
    }
};
