#include <iostream>
#include <vector>
using namespace std;

class BPlusTree {
public:
    BPlusTree(int degree) : degree(degree), root(nullptr) {}

    bool isEmpty() {
        return !root;
    }

    void add(int key, int value) {
        if (!root) {
            root = new TreeNode(degree, true);
            root->keys[0] = key;
            root->values[0] = value;
            return;
        }

        if (root->count != (degree << 1)) {
            addNode(root, key, value);
            return;
        }

        TreeNode *node = new TreeNode(degree, false);
        node->children[0] = root;
        splitChild(node, root, 0);

        if (key > node->keys[node->count - 1]) {
            node->keys[node->count - 1] = key;
        }

        int index = (node->keys[0] < key) ? 1 : 0;
        addNode(node->children[index], key, value);
        root = node;
    }

    void erase(int key) {
        if (!root) {
            return;
        }

        eraseNode(root, key);
        if (!root->count) {
            root = nullptr;
        } else if (root->count <= 1 && !root->leaf) {
            root = root->children[0];
        }
    }

    void set(int key, int value) {
        TreeNode *current = root;
        while (current) {
            int start = 0;
            int end = current->count - 1;
            while (start <= end) {
                int middle = start + ((end - start) >> 1);
                if (key > current->keys[middle]) {
                    start = middle + 1;
                } else {
                    end = middle - 1;
                }
            }

            if (current->leaf) {
                if (start < current->count && key == current->keys[start]) {
                    current->values[start] = value;
                }
                return;
            }

            if (start >= current->count) {
                return;
            }
            current = current->children[start];
        }
    }

    int get(int key) {
        TreeNode *current = root;
        while (current) {
            int start = 0;
            int end = current->count - 1;
            while (start <= end) {
                int middle = start + ((end - start) >> 1);
                if (key > current->keys[middle]) {
                    start = middle + 1;
                } else {
                    end = middle - 1;
                }
            }

            if (current->leaf) {
                if (start < current->count && key == current->keys[start]) {
                    return current->values[start];
                }
                return INT_MIN;
            }

            if (start >= current->count) {
                return INT_MIN;
            }
            current = current->children[start];
        }
        return INT_MIN;
    }

    void clear() {
        root = nullptr;
    }

private:
    struct TreeNode {
        vector<int> keys;
        vector<int> values;
        TreeNode **children;
        int count;
        bool leaf;
        TreeNode *next;

        TreeNode(int degree, bool leaf) : count(1), leaf(leaf), next(nullptr) {
            keys.assign(degree << 1, 0);
            if (leaf) {
                values.assign(degree << 1, 0);
            } else {
                children = new TreeNode *[degree << 1];
                for (int i = 0; i < (degree << 1); ++i) {
                    children[i] = nullptr;
                }
            }
        }
    };

    TreeNode *root;
    int degree;

    void addNode(TreeNode *parent, int key, int value) {
        int start = 0;
        int end = parent->count - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (key > parent->keys[middle]) {
                start = middle + 1;
            } else {
                end = middle - 1;
            }
        }

        if (parent->leaf) {
            if (start < parent->count && key == parent->keys[start]) {
                parent->values[start] = value;
                return;
            }

            for (int i = parent->count - 1; i >= start; --i) {
                parent->keys[i + 1] = parent->keys[i];
                parent->values[i + 1] = parent->values[i];
            }
            parent->keys[start] = key;
            parent->values[start] = value;
            ++parent->count;
            return;
        }

        if (start >= parent->count) {
            start = parent->count - 1;
        }

        if (parent->children[start]->count == (degree << 1)) {
            splitChild(parent, parent->children[start], start);
            if (parent->keys[start] < key) {
                ++start;
            }
        }

        if (key > parent->keys[parent->count - 1]) {
            parent->keys[parent->count - 1] = key;
        }
        addNode(parent->children[start], key, value);
    }

    void eraseNode(TreeNode *parent, int key) {
        int start = 0;
        int end = parent->count - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (key > parent->keys[middle]) {
                start = middle + 1;
            } else {
                end = middle - 1;
            }
        }

        if (parent->leaf) {
            if (key != parent->keys[start]) {
                return;
            }

            for (int i = start + 1; i < parent->count; ++i) {
                parent->keys[i - 1] = parent->keys[i];
                parent->values[i - 1] = parent->values[i];
            }
            --parent->count;
            return;
        }

        bool flag = (start == parent->count - 1);
        if (parent->children[start]->count <= degree) {
            fillChild(parent, start);
        }

        if (flag && start > parent->count - 1) {
            eraseNode(parent->children[start - 1], key);
        } else {
            eraseNode(parent->children[start], key);
        }

        if (key == parent->keys[parent->count - 1]) {
            parent->keys[parent->count - 1] = parent->children[parent->count - 1]->keys[parent->children[parent->count - 1]->count - 1];
        }
    }

    void splitChild(TreeNode *parent, TreeNode *child, int index) {
        TreeNode *node = new TreeNode(degree, child->leaf);
        copy(child->keys.begin() + degree, child->keys.begin() + child->count, node->keys.begin());
        if (child->leaf) {
            copy(child->values.begin() + degree, child->values.begin() + child->count, node->values.begin());

            node->next = child->next;
            child->next = node;
        } else {
            copy(child->children + degree, child->children + child->count, node->children);
        }

        for (int i = parent->count - 1; i > index; --i) {
            parent->keys[i + 1] = parent->keys[i];
            parent->children[i + 1] = parent->children[i];
        }
        parent->keys[index] = child->keys[degree - 1];
        parent->keys[index + 1] = node->keys[degree - 1];
        parent->children[index + 1] = node;

        node->count = degree;
        child->count = degree;
        ++parent->count;
    }

    void fillChild(TreeNode *parent, int index) {
        if (index && parent->children[index - 1]->count > degree) {
            borrowFromPrev(parent, index);
            return;
        }

        if (index != parent->count - 1 && parent->children[index + 1]->count > degree) {
            borrowFromNext(parent, index);
            return;
        }

        if (index != parent->count - 1) {
            mergeChild(parent, index);
        } else {
            mergeChild(parent, index - 1);
        }
    }

    void mergeChild(TreeNode *parent, int index) {
        TreeNode *child = parent->children[index];
        TreeNode *node = parent->children[index + 1];

        copy(node->keys.begin(), node->keys.begin() + node->count, child->keys.begin() + degree);
        if (child->leaf) {
            copy(node->values.begin(), node->values.begin() + node->count, child->values.begin() + degree);
            child->next = node->next;
        } else {
            copy(node->children, node->children + node->count, child->children + degree);
        }

        parent->keys[index] = node->keys[node->count - 1];
        for (int i = index + 2; i < parent->count; ++i) {
            parent->keys[i - 1] = parent->keys[i];
            parent->children[i - 1] = parent->children[i];
        }

        child->count += node->count;
        --parent->count;
    }

    void borrowFromPrev(TreeNode *parent, int index) {
        TreeNode *child = parent->children[index];
        TreeNode *node = parent->children[index - 1];

        for (int i = child->count - 1; i >= 0; --i) {
            child->keys[i + 1] = child->keys[i];
        }
        child->keys[0] = node->keys[node->count - 1];
        if (child->leaf) {
            for (int i = child->count - 1; i >= 0; --i) {
                child->values[i + 1] = child->values[i];
            }
            child->values[0] = node->values[node->count - 1];
        } else {
            for (int i = child->count - 1; i >= 0; --i) {
                child->children[i + 1] = child->children[i];
            }
            child->children[0] = node->children[node->count - 1];
        }

        parent->keys[index - 1] = node->keys[node->count - 2];

        ++child->count;
        --node->count;
    }

    void borrowFromNext(TreeNode *parent, int index) {
        TreeNode *child = parent->children[index];
        TreeNode *node = parent->children[index + 1];

        child->keys[child->count] = node->keys[0];
        if (child->leaf) {
            child->values[child->count] = node->values[0];
        } else {
            child->children[child->count] = node->children[0];
        }

        for (int i = 1; i < node->count; ++i) {
            node->keys[i - 1] = node->keys[i];
        }
        if (node->leaf) {
            for (int i = 1; i < node->count; ++i) {
                node->values[i - 1] = node->values[i];
            }
        } else {
            for (int i = 1; i < node->count; ++i) {
                node->children[i - 1] = node->children[i];
            }
        }

        parent->keys[index] = child->keys[child->count];

        ++child->count;
        --node->count;
    }
};
