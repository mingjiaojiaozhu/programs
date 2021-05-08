#include <iostream>
using namespace std;

class BinarySearchTree {
public:
    bool isEmpty() {
        return !root;
    }

    void add(int key, int value) {
        if (!root) {
            root = new TreeNode(key, value);
            return;
        }

        TreeNode *parent = nullptr;
        TreeNode *current = root;
        while (current) {
            if (key == current->key) {
                current->value = value;
                return;
            }

            parent = current;
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        addNode(parent, key, value);
    }

    void erase(int key) {
        if (!root) {
            return;
        }

        if (key == root->key && (!root->left || !root->right)) {
            root = root->left ? root->left : root->right;
            return;
        }

        TreeNode *parent = nullptr;
        TreeNode *current = root;
        while (current) {
            if (key == current->key) {
                break;
            }

            parent = current;
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (!current) {
            return;
        }

        if (!current->left || !current->right) {
            eraseNode(parent, current, current->left ? current->left : current->right);
            return;
        }

        TreeNode *child = current->right;
        parent = current;
        while (child->left) {
            parent = child;
            child = child->left;
        }
        current->key = child->key;
        current->value = child->value;
        eraseNode(parent, child, child->right);
    }

    void set(int key, int value) {
        TreeNode *current = root;
        while (current) {
            if (key == current->key) {
                current->value = value;
                return;
            }

            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }

    int get(int key) {
        TreeNode *current = root;
        while (current) {
            if (key == current->key) {
                return current->value;
            }

            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return INT_MIN;
    }

    void clear() {
        root = nullptr;
    }

private:
    struct TreeNode {
        int key;
        int value;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int key, int value) : key(key), value(value), left(nullptr), right(nullptr) {}
    };

    TreeNode *root;

    void addNode(TreeNode *parent, int key, int value) {
        if (key < parent->key) {
            parent->left = new TreeNode(key, value);
        } else {
            parent->right = new TreeNode(key, value);
        }
    }

    void eraseNode(TreeNode *parent, TreeNode *current, TreeNode *child) {
        if (current == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    }
};
