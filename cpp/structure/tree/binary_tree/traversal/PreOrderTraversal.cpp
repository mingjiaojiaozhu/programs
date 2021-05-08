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

class PreOrderTraversal {
public:
    vector<int> traversal(TreeNode *root) {
        vector<int> result(0);
        stack<TreeNode *> stack;
        TreeNode *current = root;
        while (current || !stack.empty()) {
            while (current) {
                result.emplace_back(current->value);

                stack.push(current);
                current = current->left;
            }
            current = stack.top()->right;
            stack.pop();
        }
        return result;
    }
};
