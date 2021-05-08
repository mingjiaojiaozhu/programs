#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    bool isPerfect(TreeNode *root) {
        if (!root) {
            return true;
        }

        queue<TreeNode *> queue;
        queue.push(root);

        int count = 0;
        bool flag = false;
        while (!queue.empty()) {
            TreeNode *current = queue.front();
            queue.pop();
            if (!current) {
                flag = true;
                continue;
            }

            if (flag) {
                return false;
            }

            ++count;
            queue.push(current->left);
            queue.push(current->right);
        }
        return !(count & (count + 1));
    }

    bool isCompleted(TreeNode *root) {
        if (!root) {
            return true;
        }

        queue<TreeNode *> queue;
        queue.push(root);

        bool flag = false;
        while (!queue.empty()) {
            TreeNode *current = queue.front();
            queue.pop();
            if ((!current->left && current->right) || (flag && (current->left || current->right))) {
                return false;
            }

            if (current->left) {
                queue.push(current->left);
            }
            if (current->right) {
                queue.push(current->right);
            } else {
                flag = true;
            }
        }
        return true;
    }

    bool isFull(TreeNode *root) {
        if (!root) {
            return true;
        }

        queue<TreeNode *> queue;
        queue.push(root);
        while (!queue.empty()) {
            TreeNode *current = queue.front();
            queue.pop();
            if ((current->left && !current->right) || (!current->left && current->right)) {
                return false;
            }

            if (current->left) {
                queue.push(current->left);
            }
            if (current->right) {
                queue.push(current->right);
            }
        }
        return true;
    }

    int nodeNum(TreeNode *root) {
        if (!root) {
            return 0;
        }

        queue<TreeNode *> queue;
        queue.push(root);

        int count = 0;
        while (!queue.empty()) {
            ++count;

            TreeNode *current = queue.front();
            queue.pop();
            if (current->left) {
                queue.push(current->left);
            }
            if (current->right) {
                queue.push(current->right);
            }
        }
        return count;
    }

    int leafNodeNum(TreeNode *root) {
        if (!root) {
            return 0;
        }

        queue<TreeNode *> queue;
        queue.push(root);

        int count = 0;
        while (!queue.empty()) {
            TreeNode *current = queue.front();
            queue.pop();
            if (!current->left && !current->right) {
                ++count;
                continue;
            }

            if (current->left) {
                queue.push(current->left);
            }
            if (current->right) {
                queue.push(current->right);
            }
        }
        return count;
    }

    int maxDepth(TreeNode *root) {
        if (!root) {
            return 0;
        }

        queue<TreeNode *> queue;
        queue.push(root);

        int count = 0;
        while (!queue.empty()) {
            ++count;

            int length = queue.size();
            for (int i = 0; i < length; ++i) {
                TreeNode *current = queue.front();
                queue.pop();
                if (current->left) {
                    queue.push(current->left);
                }
                if (current->right) {
                    queue.push(current->right);
                }
            }
        }
        return count;
    }

    TreeNode *mirror(TreeNode *root) {
        if (!root || (!root->left && !root->right)) {
            return root;
        }

        swap(root->left, root->right);

        root->left = mirror(root->left);
        root->right = mirror(root->right);
        return root;
    }
};
