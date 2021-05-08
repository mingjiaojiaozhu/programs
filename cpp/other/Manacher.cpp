#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Manacher {
public:
    string search(string text) {
        string aux = "|";
        for (char value : text) {
            aux += value;
            aux.append("|");
        }

        int border = 0;
        int middle = 0;
        int center = 0;
        int maxLength = 0;
        vector<int> buckets((text.size() << 1) + 1, 0);
        for (int i = 0; i < (int) buckets.size(); ++i) {
            if (i < border) {
                int index = (middle << 1) - i;
                buckets[i] = min(buckets[index], border - i);
                if (i + buckets[index] < border) {
                    continue;
                }
            }

            int left = i - buckets[i] - 1;
            int right = i + buckets[i] + 1;
            while (left >= 0 && right < (int) buckets.size()) {
                if (aux[left] != aux[right]) {
                    break;
                }
                ++buckets[i];

                --left;
                ++right;
            }

            border = buckets[i] + i;
            middle = i;
            if (maxLength < buckets[i]) {
                maxLength = buckets[i];
                center = i;
            }
        }

        string result = "";
        for (int i = center - maxLength; i <= center + maxLength; ++i) {
            char value = aux[i];
            if ('|' != value) {
                result += value;
            }
        }
        return result;
    }
};
