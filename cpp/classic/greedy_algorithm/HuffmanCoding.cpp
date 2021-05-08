#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

class HuffmanCoding {
public:
    string solution(string text) {
        int maxValue = *max_element(begin(text), end(text));
        int minValue = *min_element(begin(text), end(text));
        vector<TreeNode *> arrays(maxValue - minValue + 1, nullptr);

        TreeNode *current = getRoot(text, maxValue - minValue + 1, minValue, arrays);
        stack<TreeNode *> stack;
        while (current || !stack.empty()) {
            while (current) {
                string code = current->code;
                stack.push(current);

                current = current->left;
                if (current) {
                    current->code = code.append("0");
                }
            }

            current = stack.top();
            stack.pop();
            string code = current->code;

            current = current->right;
            if (current) {
                current->code = code.append("1");
            }
        }

        string result = "";
        for (char value : text) {
            result.append(arrays[value - minValue]->code);
        }
        return result;
    }

private:
    typedef struct TreeNode {
        int weight;
        TreeNode *left;
        TreeNode *right;
        string code;

        TreeNode(int weight, TreeNode *left, TreeNode *right) : weight(weight), left(left), right(right), code("") {}
    } TreeNode, *pNode;

    struct cmp {
        bool operator() (const pNode node1, const pNode node2) {
            return node1->weight > node2->weight;
        }
    };

    TreeNode *getRoot(string text, int size, int minValue, vector<TreeNode *> &arrays) {
        vector<int> buckets(size, 0);
        for (char value : text) {
            ++buckets[value - minValue];
        }

        priority_queue<pNode, vector<pNode>, cmp> queue;
        for (int i = 0; i < (int) buckets.size(); ++i) {
            TreeNode *node = new TreeNode(buckets[i], nullptr, nullptr);
            queue.push(node);
            arrays[i] = node;
        }

        while (queue.size() > 1) {
            TreeNode *left = queue.top();
            queue.pop();
            TreeNode *right = queue.top();
            queue.pop();
            queue.push(new TreeNode(left->weight + right->weight, left, right));
        }
        return queue.top();
    }
};
