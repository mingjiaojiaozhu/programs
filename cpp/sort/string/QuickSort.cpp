#include <iostream>
#include <vector>
#include <string>
using namespace std;

class QuickSort {
public:
    void sort(vector<string> &texts) {
        sort(texts, 0, texts.size() - 1, 0);
    }

private:
    void sort(vector<string> &texts, int start, int end, int digit) {
        if (start >= end) {
            return;
        }

        int pivot = getChar(texts[start], digit);
        int left = start;
        int right = end;
        int index = start + 1;
        while (index <= right) {
            int value = getChar(texts[index], digit);
            if (pivot == value) {
                ++index;
                continue;
            }

            if (value < pivot) {
                swap(texts[index], texts[left]);

                ++index;
                ++left;
            } else {
                swap(texts[index], texts[right]);
                --right;
            }
        }

        sort(texts, start, left - 1, digit);
        if (~pivot) {
            sort(texts, left, right, digit + 1);
        }
        sort(texts, right + 1, end, digit);
    }

    int getChar(string text, int digit) {
        if ((int) text.length() <= digit) {
            return -1;
        }
        return text[digit];
    }
};
