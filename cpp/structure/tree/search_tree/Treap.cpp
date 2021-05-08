#include <iostream>
#include <ctime>
using namespace std;

class Treap {
public:
    bool isEmpty() {
        return !root;
    }

    void add(int key, int value) {
        root = addNode(root, key, value);
    }

    void erase(int key) {
        root = eraseNode(root, key);
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
        int factor;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int key, int value) : key(key), value(value), left(nullptr), right(nullptr) {
            srand((unsigned int) time(nullptr));
            factor = rand() % 65536;
        }
    };

    TreeNode *root;

    TreeNode *addNode(TreeNode *parent, int key, int value) {
        if (!parent) {
            return new TreeNode(key, value);
        }

        if (key == parent->key) {
            parent->value = value;
            return parent;
        }

        if (key < parent->key) {
            parent->left = addNode(parent->left, key, value);
            if (parent->factor < parent->left->factor) {
                parent = rightRotation(parent);
            }
        } else {
            parent->right = addNode(parent->right, key, value);
            if (parent->factor < parent->right->factor) {
                parent = leftRotation(parent);
            }
        }
        return parent;
    }

    TreeNode *eraseNode(TreeNode *parent, int key) {
        if (!parent) {
            return parent;
        }

        if (key == parent->key) {
            if (parent->left && parent->right) {
                if (parent->left->factor > parent->right->factor) {
                    parent = rightRotation(parent);
                    parent->right = eraseNode(parent->right, key);
                } else {
                    parent = leftRotation(parent);
                    parent->left = eraseNode(parent->left, key);
                }
            } else {
                parent = parent->left ? parent->left : parent->right;
            }
        } else if (key < parent->key) {
            parent->left = eraseNode(parent->left, key);
        } else {
            parent->right = eraseNode(parent->right, key);
        }
        return parent;
    }

    TreeNode *leftRotation(TreeNode *current) {
        TreeNode *child = current->right;
        current->right = child->left;
        child->left = current;
        return child;
    }

    TreeNode *rightRotation(TreeNode *current) {
        TreeNode *child = current->left;
        current->left = child->right;
        child->right = current;
        return child;
    }
};
