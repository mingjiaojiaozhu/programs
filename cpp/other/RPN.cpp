#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

class RPN {
public:
    vector<string> converse(vector<string> &values) {
        stack<string> stack;
        vector<string> result(0);
        for (string value : values) {
            if (!value.compare("(")) {
                stack.push(value);
                continue;
            }

            if (!value.compare(")")) {
                while (!stack.empty()) {
                    string sign = stack.top();
                    stack.pop();
                    if (!sign.compare("(")) {
                        break;
                    }
                    result.emplace_back(sign);
                }
                continue;
            }

            if (value.compare("+") && value.compare("-") && value.compare("*") && value.compare("/")) {
                result.emplace_back(value);
                continue;
            }

            while (!stack.empty()) {
                string sign = stack.top();
                if (!sign.compare("(") || ((!value.compare("*") || !value.compare("/")) && (!sign.compare("+") || !sign.compare("-")))) {
                    break;
                }
                result.emplace_back(sign);
                stack.pop();
            }
            stack.push(value);
        }

        while (!stack.empty()) {
            result.emplace_back(stack.top());
            stack.pop();
        }
        return result;
    }

    int evaluate(vector<string> &values) {
        stack<int> stack;
        for (string value : values) {
            if (value.compare("+") && value.compare("-") && value.compare("*") && value.compare("/")) {
                stack.push(stoi(value));
                continue;
            }

            int num1 = stack.top();
            stack.pop();
            int num2 = stack.top();
            stack.pop();
            if (!value.compare("+")) {
                stack.push(num2 + num1);
            } else if (!value.compare("-")) {
                stack.push(num2 - num1);
            } else if (!value.compare("*")) {
                stack.push(num2 * num1);
            } else {
                stack.push(num2 / num1);
            }
        }
        return stack.top();
    }
};
