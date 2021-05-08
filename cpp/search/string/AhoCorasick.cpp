#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class AhoCorasick {
public:
    vector<int> search(string text, vector<string> &patterns) {
        TreeNode *root = getRoot(patterns);

        vector<int> result(patterns.size(), -1);
        TreeNode *current = root;
        for (int i = 0; i < (int) text.size(); ++i) {
            TreeNode *aux = nullptr;
            while (!aux) {
                aux = current->next[text[i] - 'a'];
                if (current == root) {
                    break;
                }

                if (!aux) {
                    current = current->failure;
                }
            }
            if (aux) {
                current = aux;
            }

            for (int index : current->indexes) {
                result[index] = i - patterns[index].size() + 1;
            }
        }
        return result;
    }

private:
    struct TreeNode {
        TreeNode **next;
        TreeNode *failure;
        vector<int> indexes;

        TreeNode(): failure(nullptr), indexes(vector<int>(0)) {
            next = new TreeNode *[26];
            for (int i = 0; i < 26; ++i) {
                next[i] = nullptr;
            }
        }
    };

    TreeNode *getRoot(vector<string> &patterns) {
        TreeNode *root = new TreeNode();
        for (int i = 0; i < (int) patterns.size(); ++i) {
            TreeNode *current = root;
            for (char value : patterns[i]) {
                int index = value - 'a';
                if (!current->next[index]) {
                    current->next[index] = new TreeNode();
                }
                current = current->next[index];
            }
            current->indexes.emplace_back(i);
        }

        queue<TreeNode *> queue;
        for (int i = 0; i < 26; ++i) {
            if (root->next[i]) {
                root->next[i]->failure = root;
                queue.push(root->next[i]);
            }
        }
        while (!queue.empty()) {
            TreeNode *current = queue.front();
            queue.pop();
            for (int i = 0; i < 26; ++i) {
                if (!current->next[i]) {
                    continue;
                }

                TreeNode *child = current->next[i];
                TreeNode *failure = current->failure;
                while (failure && !failure->next[i]) {
                    failure = failure->failure;
                }
                if (!failure) {
                    child->failure = root;
                } else {
                    child->failure = failure->next[i];
                    for (int index : failure->next[i]->indexes) {
                        child->indexes.emplace_back(index);
                    }
                }
                queue.push(child);
            }
        }
        return root;
    }
};
