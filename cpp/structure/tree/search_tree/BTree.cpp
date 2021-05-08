#include <iostream>
#include <vector>
using namespace std;

class BTree {
public:
    BTree(int degree) : degree(degree), root(nullptr) {}

    bool isEmpty() {
        return !root;
    }

    void add(int key, int value) {
        if (!root) {
            root = new TreeNode(degree, true);
            root->keys[0] = key;
            root->values[0] = value;
            ++root->count;
            return;
        }

        if (root->count != (degree << 1) - 1) {
            addNode(root, key, value);
            return;
        }

        TreeNode *node = new TreeNode(degree, false);
        node->children[0] = root;
        splitChild(node, root, 0);

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
            root = root->leaf ? nullptr : root->children[0];
        }
    }

    void set(int key, int value) {
        TreeNode *current = root;
        while (current) {
            int start = 0;
            int end = current->count - 1;
            while (start <= end) {
                int middle = start + ((end - start) >> 1);
                if (key == current->keys[middle]) {
                    current->values[middle] = value;
                    return;
                }

                if (key < current->keys[middle]) {
                    end = middle - 1;
                } else {
                    start = middle + 1;
                }
            }

            if (current->leaf) {
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
                if (key == current->keys[middle]) {
                    return current->values[middle];
                }

                if (key < current->keys[middle]) {
                    end = middle - 1;
                } else {
                    start = middle + 1;
                }
            }

            if (current->leaf) {
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

        TreeNode(int degree, bool leaf) : count(0), leaf(leaf) {
            keys.assign((degree << 1) - 1, 0);
            values.assign((degree << 1) - 1, 0);
            if (!leaf) {
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
            if (key == parent->keys[middle]) {
                parent->values[middle] = value;
                return;
            }

            if (key < parent->keys[middle]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }

        if (parent->leaf) {
            for (int i = parent->count - 1; i > end; --i) {
                parent->keys[i + 1] = parent->keys[i];
                parent->values[i + 1] = parent->values[i];
            }
            parent->keys[end + 1] = key;
            parent->values[end + 1] = value;
            ++parent->count;
            return;
        }

        if (parent->children[end + 1]->count == (degree << 1) - 1) {
            splitChild(parent, parent->children[end + 1], end + 1);
            if (parent->keys[end + 1] < key) {
                ++end;
            }
        }
        addNode(parent->children[end + 1], key, value);
    }

    void eraseNode(TreeNode *parent, int key) {
        int start = 0;
        int end = parent->count - 1;
        bool exists = false;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (key == parent->keys[middle]) {
                exists = true;
                break;
            }

            if (key < parent->keys[middle]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }

        if (!exists) {
            if (parent->leaf) {
                return;
            }

            bool flag = (start == parent->count);
            if (parent->children[start]->count < degree) {
                fillChild(parent, start);
            }

            if (flag && start > parent->count) {
                eraseNode(parent->children[start - 1], key);
            } else {
                eraseNode(parent->children[start], key);
            }
            return;
        }

        if (parent->leaf) {
            for (int i = start + 1; i < parent->count; ++i) {
                parent->keys[i - 1] = parent->keys[i];
                parent->values[i - 1] = parent->values[i];
            }
            --parent->count;
            return;
        }

        if (parent->children[start]->count >= degree) {
            TreeNode *current = parent->children[start];
            while (!current->leaf) {
                current = current->children[current->count];
            }

            parent->keys[start] = current->keys[current->count - 1];
            parent->values[start] = current->values[current->count - 1];
            eraseNode(parent->children[start], current->keys[current->count - 1]);
            return;
        }

        if (parent->children[start + 1]->count >= degree) {
            TreeNode *current = parent->children[start + 1];
            while (!current->leaf) {
                current = current->children[0];
            }

            parent->keys[start] = current->keys[0];
            parent->values[start] = current->values[0];
            eraseNode(parent->children[start + 1], current->keys[0]);
            return;
        }

        mergeChild(parent, start);
        eraseNode(parent->children[start], key);
    }

    void splitChild(TreeNode *parent, TreeNode *child, int index) {
        TreeNode *node = new TreeNode(degree, child->leaf);
        copy(child->keys.begin() + degree, child->keys.begin() + child->count, node->keys.begin());
        copy(child->values.begin() + degree, child->values.begin() + child->count, node->values.begin());
        if (!child->leaf) {
            copy(child->children + degree, child->children + child->count + 1, node->children);
        }

        for (int i = parent->count - 1; i >= index; --i) {
            parent->keys[i + 1] = parent->keys[i];
            parent->values[i + 1] = parent->values[i];
        }
        for (int i = parent->count; i > index; --i) {
            parent->children[i + 1] = parent->children[i];
        }
        parent->keys[index] = child->keys[degree - 1];
        parent->values[index] = child->values[degree - 1];
        parent->children[index + 1] = node;

        node->count = degree - 1;
        child->count = degree - 1;
        ++parent->count;
    }

    void fillChild(TreeNode *parent, int index) {
        if (index && parent->children[index - 1]->count >= degree) {
            borrowFromPrev(parent, index);
            return;
        }

        if (index != parent->count && parent->children[index + 1]->count >= degree) {
            borrowFromNext(parent, index);
            return;
        }

        if (index != parent->count) {
            mergeChild(parent, index);
        } else {
            mergeChild(parent, index - 1);
        }
    }

    void mergeChild(TreeNode *parent, int index) {
        TreeNode *child = parent->children[index];
        TreeNode *node = parent->children[index + 1];

        child->keys[degree - 1] = parent->keys[index];
        child->values[degree - 1] = parent->values[index];
        copy(node->keys.begin(), node->keys.begin() + node->count, child->keys.begin() + degree);
        copy(node->values.begin(), node->values.begin() + node->count, child->values.begin() + degree);
        if (!child->leaf) {
            copy(node->children, node->children + node->count + 1, child->children + degree);
        }

        for (int i = index + 1; i < parent->count; ++i) {
            parent->keys[i - 1] = parent->keys[i];
            parent->values[i - 1] = parent->values[i];
        }
        for (int i = index + 2; i <= parent->count; ++i) {
            parent->children[i - 1] = parent->children[i];
        }

        child->count += node->count + 1;
        --parent->count;
    }

    void borrowFromPrev(TreeNode *parent, int index) {
        TreeNode *child = parent->children[index];
        TreeNode *node = parent->children[index - 1];

        for (int i = child->count - 1; i >= 0; --i) {
            child->keys[i + 1] = child->keys[i];
            child->values[i + 1] = child->values[i];
        }
        child->keys[0] = parent->keys[index - 1];
        child->values[0] = parent->values[index - 1];
        if (!child->leaf) {
            for (int i = child->count; i >= 0; --i) {
                child->children[i + 1] = child->children[i];
            }
            child->children[0] = node->children[node->count];
        }

        parent->keys[index - 1] = node->keys[node->count - 1];
        parent->values[index - 1] = node->values[node->count - 1];

        ++child->count;
        --node->count;
    }

    void borrowFromNext(TreeNode *parent, int index) {
        TreeNode *child = parent->children[index];
        TreeNode *node = parent->children[index + 1];

        child->keys[child->count] = parent->keys[index];
        child->values[child->count] = parent->values[index];
        if (!child->leaf) {
            child->children[child->count + 1] = node->children[0];
        }

        parent->keys[index] = node->keys[0];
        parent->values[index] = node->values[0];

        for (int i = 1; i < node->count; ++i) {
            node->keys[i - 1] = node->keys[i];
            node->values[i - 1] = node->values[i];
        }
        if (!node->leaf) {
            for (int i = 1; i <= node->count; ++i) {
                node->children[i - 1] = node->children[i];
            }
        }

        ++child->count;
        --node->count;
    }
};
