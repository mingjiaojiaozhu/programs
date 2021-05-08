#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Karatsuba {
public:
    string multiply(string num1, string num2) {
        int length = max(num1.size(), num2.size());
        if (length <= 4) {
            return to_string(stoi(num1) * stoi(num2));
        }

        if (length > (int) num1.length()) {
            num1 = fillHead(num1, length - num1.size());
        }
        if (length > (int) num2.length()) {
            num2 = fillHead(num2, length - num2.size());
        }

        int halfSize = length >> 1;
        string num1Head = num1.substr(0, halfSize);
        string num1Tail = num1.substr(halfSize);
        string num2Head = num2.substr(0, halfSize);
        string num2Tail = num2.substr(halfSize);
        string aux1 = multiply(num1Head, num2Head);
        string aux2 = multiply(num1Tail, num2Tail);
        return add(add(fillTail(aux1, (length - halfSize) << 1), fillTail(subtract(multiply(add(num1Head, num1Tail), add(num2Head, num2Tail)), add(aux1, aux2)), length - halfSize)), aux2);
    }

private:
    string add(string num1, string num2) {
        vector<int> values1 = stringToArrays(num1);
        vector<int> values2 = stringToArrays(num2);

        vector<int> result(max(num1.size(), num2.size()) + 1, 0);
        copy(values1.begin(), values1.end(), result.begin());
        for (int i = 0; i < (int) values2.size(); ++i) {
            result[i] += values2[i];
            if (result[i] >= 10) {
                result[i] -= 10;
                ++result[i + 1];
            }
        }

        int index = values2.size();
        while (index < (int) values1.size() - 1 && result[index] >= 10) {
            result[index] -= 10;
            ++result[index + 1];
            ++index;
        }
        return arraysToString(result);
    }

    string subtract(string num1, string num2) {
        vector<int> values1 = stringToArrays(num1);
        vector<int> values2 = stringToArrays(num2);
        for (int i = 0; i < (int) values2.size(); ++i) {
            values1[i] -= values2[i];
            if (values1[i] < 0) {
                values1[i] += 10;
                --values1[i + 1];
            }
        }

        int index = values2.size();
        while (index < (int) values1.size() - 1 && values1[index] < 0) {
            values1[index] += 10;
            --values1[index + 1];
            ++index;
        }
        return arraysToString(values1);
    }

    string fillHead(string num, int length) {
        stringstream stream;
        stream << setw(length) << setfill('0') << 0;
        return stream.str() + num;
    }

    string fillTail(string num, int length) {
        stringstream stream;
        stream << setw(length) << setfill('0') << 0;
        return num + stream.str();
    }

    vector<int> stringToArrays(string num) {
        vector<int> result(0);
        for (char value : num) {
            result.emplace_back(value - '0');
        }
        reverse(result.begin(), result.end());
        return result;
    }

    string arraysToString(vector<int> &values) {
        reverse(values.begin(), values.end());
        int index = 0;
        while (index < (int) values.size() - 1 && !values[index]) {
            ++index;
        }

        string result = "";
        for (int i = index; i < (int) values.size(); ++i) {
            result += to_string(values[i]);
        }
        return result;
    }
};
