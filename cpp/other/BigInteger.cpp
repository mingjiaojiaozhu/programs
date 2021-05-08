#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class BigInteger {
public:
    string add(string num1, string num2) {
        string result = "";
        int carry = 0;
        for (int i = 1; i <= (int) max(num1.size(), num2.size()); ++i) {
            int value1 = (i <= (int) num1.size()) ? num1[num1.size() - i] - '0' : 0;
            int value2 = (i <= (int) num2.size()) ? num2[num2.size() - i] - '0' : 0;
            int value = value1 + value2 + carry;
            carry = value / 10;
            result.append(to_string(value % 10));
        }
        if (carry) {
            result.append(to_string(carry));
        }
        reverse(result.begin(), result.end());
        return result;
    }

    string subtract(string num1, string num2) {
        if (!greater(num1, num2)) {
            return "-" + subtract(num2, num1);
        }

        string result = "";
        int borrow = 0;
        for (int i = 1; i <= (int) num1.size(); ++i) {
            int value1 = num1[num1.size() - i] - '0';
            int value2 = (i <= (int) num2.size()) ? num2[num2.size() - i] - '0' : 0;
            int value = value1 - value2 - borrow;
            borrow = 0;
            if (value < 0) {
                value += 10;
                borrow = 1;
            }
            result.append(to_string(value));
        }

        int index = result.size() - 1;
        while (index > 0 && '0' == result[index]) {
            --index;
        }
        reverse(result.begin(), result.end());
        return result.substr(result.size() - 1 - index);
    }

    string multiply(string num1, string num2) {
        vector<char> values(num1.size() + num2.size(), '0');
        for (int i = 1; i <= (int) num1.size(); ++i) {
            int value1 = num1[num1.size() - i] - '0';
            for (int j = 1; j <= (int) num2.size(); ++j) {
                int value2 = num2[num2.size() - j] - '0';
                int value = value1 * value2;
                int index = i + j - 2;
                addValues(values, index, value % 10);
                addValues(values, index + 1, value / 10);
            }
        }

        int index = values.size() - 1;
        while (index > 0 && '0' == values[index]) {
            --index;
        }
        string result = "";
        for (int i = index; i >= 0; --i) {
            result += values[i];
        }
        return result;
    }

    vector<string> divide(string num1, string num2) {
        vector<string> result(2, "0");
        while (greater(num1, num2)) {
            int diff = num1.size() - num2.size();
            string aux1 = fillTail(num2, diff);
            string aux2 = fillTail("1", diff);
            if (!greater(num1, aux1)) {
                aux1.erase(aux1.end() - 1);
                aux2.erase(aux2.end() - 1);
            }
            while (greater(num1, aux1)) {
                num1 = subtract(num1, aux1);
                result[0] = add(result[0], aux2);
            }
        }
        result[1] = num1;
        return result;
    }

private:
    void addValues(vector<char> &values, int index, int value) {
        values[index] += value;
        if (values[index] > '9') {
            values[index] -= 10;
            ++values[index + 1];
        }
    }

    bool greater(string num1, string num2) {
        if (num1.size() != num2.size()) {
            return num1.size() > num2.size();
        }
        return num1.compare(num2) >= 0;
    }

    string fillTail(string num, int length) {
        stringstream stream;
        stream << setw(length) << setfill('0') << 0;
        return num + stream.str();
    }
};
