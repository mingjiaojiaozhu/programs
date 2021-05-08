#include <iostream>
using namespace std;

class SplayTree {
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
                splay(current);
                return;
            }

            parent = current;
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        current = addNode(parent, key, value);
        splay(current);
    }

    void erase(int key) {
        if (!root) {
            return;
        }

        if (key == root->key && (!root->left || !root->right)) {
            root = root->left ? root->left : root->right;
            return;
        }

        TreeNode *current = root;
        while (current) {
            if (key == current->key) {
                break;
            }

            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (!current) {
            return;
        }

        splay(current);
        if (!current->left || !current->right) {
            root = current->left ? current->left : current->right;
            return;
        }

        TreeNode *child = current->right;
        TreeNode *parent = current;
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
                splay(current);
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
                splay(current);
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

    TreeNode *addNode(TreeNode *parent, int key, int value) {
        TreeNode *child = new TreeNode(key, value);
        if (key < parent->key) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        return child;
    }

    void eraseNode(TreeNode *parent, TreeNode *current, TreeNode *child) {
        if (current == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    }

    void splay(TreeNode *pivot) {
        TreeNode *aux = new TreeNode(0, 0);
        TreeNode *left = aux;
        TreeNode *right = aux;

        TreeNode *current = root;
        while (pivot != current) {
            if (pivot->key < current->key) {
                if (pivot->key < current->left->key) {
                    current = leftRotation(current);
                }
                right->left = current;
                right = current;
                current = current->left;
            } else {
                if (pivot->key > current->right->key) {
                    current = rightRotation(current);
                }
                left->right = current;
                left = current;
                current = current->right;
            }
        }

        left->right = current->left;
        right->left = current->right;
        current->left = aux->right;
        current->right = aux->left;
        root = current;
    }

    TreeNode *leftRotation(TreeNode *current) {
        TreeNode *child = current->left;
        current->left = child->right;
        child->right = current;
        return child;
    }

    TreeNode *rightRotation(TreeNode *current) {
        TreeNode *child = current->right;
        current->right = child->left;
        child->left = current;
        return child;
    }
};
