#include <iostream>
#include <string>
using namespace std;

class RabinKarp {
public:
    int search(string text, string pattern) {
        int code = getHashCode(text, pattern.size());
        int patternCode = getHashCode(pattern, pattern.size());
        for (int i = 0; i <= (int) text.size() - (int) pattern.size(); ++i) {
            if (code == patternCode) {
                int index = i;
                int patternIndex = 0;
                while (index < (int) text.size()) {
                    if (text[index] != pattern[patternIndex]) {
                        break;
                    }

                    if (patternIndex == pattern.size() - 1) {
                        return index - patternIndex;
                    }
                    ++index;
                    ++patternIndex;
                }
            }

            if (i < (int) text.size() - (int) pattern.size()) {
                code += text[i + pattern.size()] - text[i];
            }
        }
        return -1;
    }

private:
    int getHashCode(string text, int length) {
        int code = 0;
        for (int i = 0; i < length; ++i) {
            code += text[i] - 'a';
        }
        return code;
    }
};
