#include <iostream>
using namespace std;

class BinomialHeap {
public:
    BinomialHeap() : root(nullptr) {}

    bool isEmpty() {
        return !root;
    }

    void add(int value) {
        if (!search(root, value)) {
            root = !root ? new TreeNode(value) : combine(root, new TreeNode(value));
        }
    }

    void erase(int value) {
        TreeNode *node = search(root, value);
        if (!node) {
            return;
        }

        TreeNode *parent = node->parent;
        while (parent) {
            swap(node->value, parent->value);

            node = parent;
            parent = node->parent;
        }

        TreeNode *pivot = nullptr;
        TreeNode *current = root;
        while (current != node) {
            pivot = current;
            current = current->next;
        }

        if (pivot) {
            pivot->next = node->next;
        } else {
            root = node->next;
        }
        root = combine(root, reverse(node->child));
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
        if (!root) {
            return INT_MIN;
        }

        TreeNode *pivot = root;
        TreeNode *current = root->next;
        while (current) {
            if (pivot->value > current->value) {
                pivot = current;
            }
            current = current->next;
        }
        return pivot->value;
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
        int degree;
        TreeNode *child;
        TreeNode *parent;
        TreeNode *next;

        TreeNode(int value) : value(value), degree(0), child(nullptr), parent(nullptr), next(nullptr) {}
    };

    TreeNode *root;

    TreeNode *combine(TreeNode *node1, TreeNode *node2) {
        TreeNode *head = merge(node1, node2);
        if (!head) {
            return head;
        }

        TreeNode *parent = nullptr;
        TreeNode *current = head;
        while (current->next) {
            TreeNode *next = current->next;
            if ((current->degree != next->degree) || (next->next && next->degree == next->next->degree)) {
                parent = current;
                current = next;
            } else if (current->value <= next->value) {
                current->next = next->next;
                link(current, next);
            } else {
                if (!parent) {
                    head = next;
                } else {
                    parent->next = next;
                }
                link(next, current);
                current = next;
            }
        }
        return head;
    }

    TreeNode *merge(TreeNode *node1, TreeNode *node2) {
        if (!node1 || !node2) {
            return node1 ? node1 : node2;
        }

        TreeNode *parent = nullptr;
        TreeNode *head = nullptr;
        while (node1 && node2) {
            TreeNode *pivot = nullptr;
            if (node1->degree <= node2->degree) {
                pivot = node1;
                node1 = node1->next;
            } else {
                pivot = node2;
                node2 = node2->next;
            }

            if (!parent) {
                parent = pivot;
                head = pivot;
            } else {
                parent->next = pivot;
                parent = pivot;
            }
            pivot->next = node1 ? node1: node2;
        }
        return head;
    }

    TreeNode *reverse(TreeNode *node) {
        if (!node) {
            return node;
        }

        node->parent = nullptr;
        TreeNode *tail = nullptr;
        while (node->next) {
            TreeNode *next = node->next;
            node->next = tail;
            tail = node;
            node = next;
            node->parent = nullptr;
        }
        node->next = tail;
        return node;
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
        TreeNode *child = node->child;
        while (child) {
            if (node->value < child->value) {
                child = child->next;
                continue;
            }

            TreeNode *pivot = child;
            while (child->next) {
                if (child->next->value < pivot->value) {
                    pivot = child->next;
                }
                child = child->next;
            }
            swap(node->value, pivot->value);

            node = pivot;
            child = node->child;
        }
    }

    void decrease(TreeNode *node) {
        TreeNode *parent = node->parent;
        while (parent && node->value < parent->value) {
            swap(node->value, parent->value);

            node = parent;
            parent = node->parent;
        }
    }

    void link(TreeNode *parent, TreeNode *child) {
        child->parent = parent;
        child->next = parent->child;
        parent->child = child;
        ++parent->degree;
    }
};
