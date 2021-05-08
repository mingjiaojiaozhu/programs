#include <iostream>
using namespace std;

class RedBlackTree {
public:
    bool isEmpty() {
        return !root;
    }

    void add(int key, int value) {
        if (!root) {
            root = new TreeNode(key, value, black, nullptr);
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
    static const char red = '0';
    static const char black = '1';

    struct TreeNode {
        int key;
        int value;
        char color;
        TreeNode *left;
        TreeNode *right;
        TreeNode *parent;

        TreeNode(int key, int value, char color, TreeNode *parent) : key(key), value(value), color(color), left(nullptr), right(nullptr), parent(parent) {}
    };

    TreeNode *root;

    void addNode(TreeNode *parent, int key, int value) {
        TreeNode *child = new TreeNode(key, value, red, parent);
        if (key < parent->key) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        addFixup(child);
    }

    void eraseNode(TreeNode *parent, TreeNode *current, TreeNode *child) {
        char color = current->color;
        if (current == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }

        if (child) {
            child->parent = parent;
        }

        if (black == color) {
            eraseFixup(child, parent);
        }
    }

    void addFixup(TreeNode *current) {
        TreeNode *parent = current->parent;
        while (parent && red == parent->color) {
            TreeNode *grandParent = parent->parent;
            if (parent == grandParent->left) {
                current = addFixupNode(current, parent, grandParent, grandParent->right, parent->right, true);
            } else {
                current = addFixupNode(current, parent, grandParent, grandParent->left, parent->left, false);
            }
            parent = current->parent;
        }
        root->color = black;
    }

    void eraseFixup(TreeNode *current, TreeNode *parent) {
        while ((!current || black == current->color) && current != root) {
            if (parent->left == current) {
                current = eraseFixupNode(parent, parent->right, true);
            } else {
                current = eraseFixupNode(parent, parent->left, false);
            }
            parent = current->parent;
        }

        if (current) {
            current->color = black;
        }
    }

    TreeNode *addFixupNode(TreeNode *current, TreeNode *parent, TreeNode *grandParent, TreeNode *uncle, TreeNode *brother, bool isLeft) {
        if (uncle && red == uncle->color) {
            uncle->color = black;
            parent->color = black;
            grandParent->color = red;
            return grandParent;
        }

        if (brother == current) {
            if (isLeft) {
                leftRotation(parent);
            } else {
                rightRotation(parent);
            }
            swap(parent, current);
        }

        parent->color = black;
        grandParent->color = red;
        if (isLeft) {
            rightRotation(grandParent);
        } else {
            leftRotation(grandParent);
        }
        return current;
    }

    TreeNode *eraseFixupNode(TreeNode *parent, TreeNode *brother, bool isLeft) {
        if (red == brother->color) {
            brother->color = black;
            parent->color = red;

            if (isLeft) {
                leftRotation(parent);
                brother = parent->right;
            } else {
                rightRotation(parent);
                brother = parent->left;
            }
        }

        if ((!brother->left || black == brother->left->color) && (!brother->right || black == brother->right->color)) {
            brother->color = red;
            return parent;
        }

        if (isLeft && (!brother->right || black == brother->right->color)) {
            brother->left->color = black;
            brother->color = red;
            rightRotation(brother);
            brother = parent->right;
        }
        if (!isLeft && (!brother->left || black == brother->left->color)) {
            brother->right->color = black;
            brother->color = red;
            leftRotation(brother);
            brother = parent->left;
        }

        brother->color = parent->color;
        parent->color = black;
        if (isLeft) {
            brother->right->color = black;
            leftRotation(parent);
        } else {
            brother->left->color = black;
            rightRotation(parent);
        }
        return root;
    }

    void leftRotation(TreeNode *current) {
        TreeNode *child = current->right;
        current->right = child->left;
        if (child->left) {
            child->left->parent = current;
        }
        child->parent = current->parent;

        if (!current->parent) {
            root = child;
        } else {
            if (current->parent->left == current) {
                current->parent->left = child;
            } else {
                current->parent->right = child;
            }
        }
        child->left = current;
        current->parent = child;
    }

    void rightRotation(TreeNode *current) {
        TreeNode *child = current->left;
        current->left = child->right;
        if (child->right) {
            child->right->parent = current;
        }
        child->parent = current->parent;

        if (!current->parent) {
            root = child;
        } else {
            if (current->parent->left == current) {
                current->parent->left = child;
            } else {
                current->parent->right = child;
            }
        }
        child->right = current;
        current->parent = child;
    }
};
