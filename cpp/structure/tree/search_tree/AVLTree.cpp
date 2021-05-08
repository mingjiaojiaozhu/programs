#include <iostream>
using namespace std;

class AVLTree {
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
        int height;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int key, int value) : key(key), value(value), height(1), left(nullptr), right(nullptr) {}
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
            if (getHeight(parent->left) - getHeight(parent->right) >= 2) {
                if (key < parent->left->key) {
                    parent = leftLeftRotation(parent);
                } else {
                    parent = leftRightRotation(parent);
                }
            }
        } else {
            parent->right = addNode(parent->right, key, value);
            if (getHeight(parent->right) - getHeight(parent->left) >= 2) {
                if (key > parent->right->key) {
                    parent = rightRightRotation(parent);
                } else {
                    parent = rightLeftRotation(parent);
                }
            }
        }
        parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1;
        return parent;
    }

    TreeNode *eraseNode(TreeNode *parent, int key) {
        if (!parent) {
            return parent;
        }

        if (key == parent->key) {
            if (parent->left && parent->right) {
                TreeNode *current = parent->right;
                while (current->left) {
                    current = current->left;
                }
                parent->key = current->key;
                parent->value = current->value;
                parent->right = eraseNode(parent->right, key);
            } else {
                parent = parent->left ? parent->left : parent->right;
            }
        } else if (key < parent->key) {
            parent->left = eraseNode(parent->left, key);
            if (getHeight(parent->right) - getHeight(parent->left) >= 2) {
                if (getHeight(parent->right->right) > getHeight(parent->right->left)) {
                    parent = rightRightRotation(parent);
                } else {
                    parent = rightLeftRotation(parent);
                }
            }
        } else {
            parent->right = eraseNode(parent->right, key);
            if (getHeight(parent->left) - getHeight(parent->right) >= 2) {
                if (getHeight(parent->left->right) < getHeight(parent->left->left)) {
                    parent = leftLeftRotation(parent);
                } else {
                    parent = leftRightRotation(parent);
                }
            }
        }

        if (parent) {
            parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1;
        }
        return parent;
    }

    int getHeight(TreeNode *current) {
        if (!current) {
            return 0;
        }
        return current->height;
    }

    TreeNode *leftLeftRotation(TreeNode *current) {
        TreeNode *child = current->left;
        current->left = child->right;
        child->right = current;

        current->height = max(getHeight(current->left), getHeight(current->right)) + 1;
        child->height = max(getHeight(child->left), getHeight(child->right)) + 1;
        return child;
    }

    TreeNode *rightRightRotation(TreeNode *current) {
        TreeNode *child = current->right;
        current->right = child->left;
        child->left = current;

        current->height = max(getHeight(current->left), getHeight(current->right)) + 1;
        child->height = max(getHeight(child->left), getHeight(child->right)) + 1;
        return child;
    }

    TreeNode *leftRightRotation(TreeNode *current) {
        current->left = rightRightRotation(current->left);
        return leftLeftRotation(current);
    }

    TreeNode *rightLeftRotation(TreeNode *current) {
        current->right = leftLeftRotation(current->right);
        return rightRightRotation(current);
    }
};
