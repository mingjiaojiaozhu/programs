#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
};

class PostOrderTraversal {
public:
    vector<int> traversal(TreeNode *root) {
        vector<int> result(0);
        TreeNode *current = root;
        while (current) {
            if (!current->left) {
                current = current->right;
                continue;
            }

            TreeNode *aux = current->left;
            while (aux->right && aux->right != current) {
                aux = aux->right;
            }
            if (!aux->right) {
                aux->right = current;
                current = current->left;
            } else {
                aux->right = nullptr;
                traversal(current->left, result);
                current = current->right;
            }
        }
        traversal(root, result);
        return result;
    }

private:
    void traversal(TreeNode *parent, vector<int> &result) {
        TreeNode *tail = reverse(parent);
        TreeNode *current = tail;
        while (current) {
            result.emplace_back(current->value);
            current = current->right;
        }
        reverse(tail);
    }

    TreeNode *reverse(TreeNode *current) {
        TreeNode *prev = nullptr;
        while (current) {
            TreeNode *next = current->right;
            current->right = prev;
            prev = current;
            current = next;
        }
        return prev;
    }
};
