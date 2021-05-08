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

class PostOrderTraversal {
public:
    vector<int> traversal(TreeNode *root) {
        vector<int> result(0);
        stack<TreeNode *> stack;
        stack.push(root);
        TreeNode *current = nullptr;
        while (!stack.empty()) {
            TreeNode *aux = stack.top();
            if (aux->left && current != aux->left && current != aux->right) {
                stack.push(aux->left);
            } else if (aux->right && current != aux->right) {
                stack.push(aux->right);
            } else {
                result.emplace_back(aux->value);
                current = aux;
                stack.pop();
            }
        }
        return result;
    }
};
