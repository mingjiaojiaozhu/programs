#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
};

class InOrderTraversal {
public:
    vector<int> traversal(TreeNode *root) {
        vector<int> result(0);
        stack<TreeNode *> stack;
        TreeNode *current = root;
        while (current || !stack.empty()) {
            while (current) {
                stack.push(current);
                current = current->left;
            }

            current = stack.top();
            stack.pop();
            result.emplace_back(current->value);

            current = current->right;
        }
        return result;
    }
};
