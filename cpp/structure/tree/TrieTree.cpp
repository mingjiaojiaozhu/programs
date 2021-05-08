#include <iostream>
#include <vector>
using namespace std;

class TrieTree {
public:
    TrieTree() : root(new TreeNode()) {}

    bool isEmpty() {
        for (int i = 0; i < 26; ++i) {
            if (root->next[i]) {
                return false;
            }
        }
        return true;
    }

    void add(string text) {
        TreeNode *current = root;
        for (char value : text) {
            int index = value - 'a';
            if (!current->next[index]) {
                current->next[index] = new TreeNode();
                ++current->depth;
            }
            current = current->next[index];
        }
        current->ended = true;
    }

    void erase(string text) {
        int index = text[0] - 'a';
        root->next[index] = eraseNode(root->next[index], text, text.size(), 1);
    }

    bool contains(string text) {
        TreeNode *current = root;
        for (char value : text) {
            int index = value - 'a';
            TreeNode *next = current->next[index];
            if (!next) {
                return false;
            }
            current = next;
        }
        return current->ended;
    }

    void clear() {
        for (int i = 0; i < 26; ++i) {
            root->next[i] = nullptr;
        }
    }

private:
    struct TreeNode {
        TreeNode **next;
        int depth;
        bool ended;

        TreeNode(): depth(0), ended(false) {
            next = new TreeNode *[26];
            for (int i = 0; i < 26; ++i) {
                next[i] = nullptr;
            }
        }
    };

    TreeNode *root;

    TreeNode *eraseNode(TreeNode *current, string text, int depth, int pos) {
        if (!current) {
            return nullptr;
        }

        if (pos >= depth) {
            if (!current->depth) {
                return nullptr;
            }
            current->ended = false;
            return current;
        }

        int index = text[pos] - 'a';
        current->next[index] = eraseNode(current->next[index], text, depth, pos + 1);
        if (current->next[index]) {
            return current;
        }

        if (current->depth) {
            --current->depth;
        }
        if (!current->depth && !current->ended) {
            return nullptr;
        }
        return current;
    }
};
