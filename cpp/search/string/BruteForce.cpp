#include <iostream>
#include <string>
using namespace std;

class BruteForce {
public:
    int search(string text, string pattern) {
        int index = 0;
        int patternIndex = 0;
        while (index < (int) text.size()) {
            if (text[index] != pattern[patternIndex]) {
                index += 1 - patternIndex;
                patternIndex = 0;
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
};
