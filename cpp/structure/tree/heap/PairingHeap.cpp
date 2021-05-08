#include <iostream>
using namespace std;

class PairingHeap {
public:
    PairingHeap() : root(nullptr) {}

    bool isEmpty() {
        return !root;
    }

    void add(int value) {
        if (!search(root, value)) {
            root = !root ? new TreeNode(value) : merge(root, new TreeNode(value));
        }
    }

    void erase(int value) {
        TreeNode *node = search(root, value);
        if (!node) {
            return;
        }

        if (value != root->value) {
            node->value = root->value - 1;
            decrease(node);
        }

        TreeNode *current = root;
        if (!current->child) {
            root = nullptr;
        } else {
            TreeNode *child = current->child;
            child->parent = nullptr;
            root = combine(child);
        }
    }

    void set(int target, int value) {
        TreeNode *node = search(root, target);
        if (node && target != value && !search(root, value)) {
            node->value = value;
            if (target < value) {
                increase(node);
            } else {
                decrease(node);
            }
        }
    }

    int getRoot() {
        if (root) {
            return root->value;
        }
        return INT_MIN;
    }

    bool contains(int value) {
        return nullptr != search(root, value);
    }

    void clear() {
        root = nullptr;
    }

private:
    struct TreeNode {
        int value;
        TreeNode *child;
        TreeNode *parent;
        TreeNode *next;

        TreeNode(int value) : value(value), child(nullptr), parent(nullptr), next(nullptr) {}
    };

    TreeNode *root;

    TreeNode *merge(TreeNode *node1, TreeNode *node2) {
        if (!node1 || !node2) {
            return node1 ? node1 : node2;
        }

        if (node1->value < node2->value) {
            TreeNode *next = node2->next;
            node1->next = next;
            if (next) {
                next->parent = node1;
            }

            TreeNode *child = node1->child;
            node2->parent = node1;
            node2->next = child;
            if (child) {
                child->parent = node2;
            }
            node1->child = node2;
            return node1;
        }

        TreeNode *parent = node1->parent;
        node2->parent = parent;
        if (parent && parent->child != node1) {
            parent->next = node2;
        }

        TreeNode *child = node2->child;
        node1->parent = node2;
        node1->next = child;
        if (child) {
            child->parent = node1;
        }
        node2->child = node1;
        return node2;
    }

    TreeNode *combine(TreeNode *node) {
        TreeNode *current = node;
        TreeNode *next = current->next;
        TreeNode *tail = current;

        bool flag = true;
        while (next) {
            tail = merge(current, next);
            current = tail->next;
            next = current ? current->next : nullptr;

            if (!flag && !current) {
                break;
            }
            flag = false;
        }

        if (current) {
            tail = current;
        }

        TreeNode *parent = tail->parent;
        while (parent) {
            tail = merge(parent, tail);
            parent = tail->parent;
        }
        return tail;
    }

    TreeNode *search(TreeNode *node, int value) {
        while (node) {
            if (value == node->value) {
                return node;
            }

            TreeNode *child = search(node->child, value);
            if (child) {
                return child;
            }
            node = node->next;
        }
        return nullptr;
    }

    void increase(TreeNode *node) {
        int pivot = node->value;
        while (node->child && pivot < node->child->value) {
            node->value = node->child->value;
            node = node->child;
        }
        node->value = pivot;
    }

    void decrease(TreeNode *node) {
        TreeNode *parent = node->parent;
        if (parent->child == node) {
            parent->child = node->next;
        } else {
            parent->next = node->next;
        }
        if (node->next) {
            node->next->parent = parent;
        }

        node->parent = nullptr;
        node->next = nullptr;
        root = merge(node, root);
    }
};
