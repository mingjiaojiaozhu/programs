#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
};

class LevelOrderTraversal {
public:
    vector<int> traversal(TreeNode *root) {
        vector<int> result(0);
        queue<TreeNode *> queue;
        queue.push(root);
        while (!queue.empty()) {
            TreeNode *current = queue.front();
            queue.pop();
            result.emplace_back(current->value);

            if (current->left) {
                queue.push(current->left);
            }
            if (current->right) {
                queue.push(current->right);
            }
        }
        return result;
    }
};
