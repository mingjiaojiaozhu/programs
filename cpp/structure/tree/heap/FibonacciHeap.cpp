#include <iostream>
#include <vector>
using namespace std;

class FibonacciHeap {
public:
    FibonacciHeap() : root(nullptr), length(0) {}

    bool isEmpty() {
        return !root;
    }

    void add(int value) {
        if (search(root, value)) {
            return;
        }

        if (!root) {
            root = new TreeNode(value);
            root->left = root;
            root->right = root;
        } else {
            TreeNode *node = new TreeNode(value);
            addNode(node, root);
            if (value < root->value) {
                root = node;
            }
        }
        ++length;
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
        while (current->child) {
            TreeNode *child = current->child;
            eraseNode(child);
            current->child = (child->right != child) ? child->right : nullptr;
            addNode(child, root);
            child->parent = nullptr;
        }

        eraseNode(current);
        root = (current->right != current) ? current->right : nullptr;
        if (current->right != current) {
            combine();
        }
        --length;
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
        length = 0;
    }

private:
    struct TreeNode {
        int value;
        int degree;
        TreeNode *child;
        TreeNode *parent;
        TreeNode *left;
        TreeNode *right;
        bool marked;

        TreeNode(int value) : value(value), degree(0), child(nullptr), parent(nullptr), left(nullptr), right(nullptr), marked(false) {}
    };

    TreeNode *root;
    int length;

    void combine() {
        int maxDegree = (int) ceil(log(length) / log(2));
        vector<TreeNode *> heads(maxDegree + 1, nullptr);

        while (root) {
            TreeNode *current = root;
            if (current == current->right) {
                root = nullptr;
            } else {
                eraseNode(current);
                root = current->right;
            }
            current->left = current;
            current->right = current;

            int degree = current->degree;
            while (heads[degree]) {
                TreeNode *node = heads[degree];
                if (current->value > node->value) {
                    swap(current, node);
                }

                link(node, current);
                heads[degree] = nullptr;
                ++degree;
            }
            heads[degree] = current;
        }

        for (TreeNode *head : heads) {
            if (!head) {
                continue;
            }

            if (!root) {
                root = head;
            } else {
                addNode(head, root);
                if (head->value < root->value) {
                    root = head;
                }
            }
        }
    }

    TreeNode *search(TreeNode *node, int value) {
        if (!node) {
            return nullptr;
        }

        TreeNode *current = node;
        bool flag = true;
        while (flag || current != node) {
            flag = false;
            if (current->value == value) {
                return current;
            }

            TreeNode *child = search(current->child, value);
            if (child) {
                return child;
            }
            current = current->right;
        }
        return nullptr;
    }

    void increase(TreeNode *node) {
        while (node->child) {
            TreeNode *child = node->child;
            eraseNode(child);
            if (child->right == child) {
                node->child = nullptr;
            } else {
                node->child = child->right;
            }

            addNode(child, root);
            child->parent = nullptr;
        }
        node->degree = 0;

        TreeNode *parent = node->parent;
        if (parent) {
            cut(node, parent);
            cascadingCut(parent);
        } else if (root == node) {
            TreeNode *right = node->right;
            while (right != node) {
                if (node->value > right->value) {
                    root = right;
                }
                right = right->right;
            }
        }
    }

    void decrease(TreeNode *node) {
        TreeNode *parent = node->parent;
        if (parent && node->value < parent->value) {
            cut(node, parent);
            cascadingCut(parent);
        }

        if (node->value < root->value) {
            root = node;
        }
    }

    void link(TreeNode *parent, TreeNode *child) {
        eraseNode(parent);
        if (!child->child) {
            child->child = parent;
        } else {
            addNode(parent, child->child);
        }

        parent->parent = child;
        parent->marked = false;
        ++child->degree;
    }

    void addNode(TreeNode *node1, TreeNode *node2) {
        node2->left->right = node1;
        node1->left = node2->left;
        node1->right = node2;
        node2->left = node1;
    }

    void eraseNode(TreeNode *node) {
        node->left->right = node->right;
        node->right->left = node->left;
    }

    void cut(TreeNode *node, TreeNode *parent) {
        eraseNode(node);
        setDegree(parent, node->degree);
        parent->child = (node != node->right) ? node->right : nullptr;

        node->parent = nullptr;
        node->left = node;
        node->right = node;
        node->marked = false;
        addNode(node, root);
    }

    void cascadingCut(TreeNode *node) {
        TreeNode *parent = node->parent;
        if (parent) {
            if (!node->marked) {
                node->marked = true;
            } else {
                cut(node, parent);
                cascadingCut(parent);
            }
        }
    }

    void setDegree(TreeNode *parent, int degree) {
        parent->degree -= degree;
        if (parent->parent) {
            setDegree(parent->parent, degree);
        }
    }
};
