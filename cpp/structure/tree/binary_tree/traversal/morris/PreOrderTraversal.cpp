#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
};

class PreOrderTraversal {
public:
    vector<int> traversal(TreeNode *root) {
        vector<int> result(0);
        TreeNode *current = root;
        while (current) {
            if (!current->left) {
                result.emplace_back(current->value);
                current = current->right;
                continue;
            }

            TreeNode *aux = current->left;
            while (aux->right && aux->right != current) {
                aux = aux->right;
            }
            if (!aux->right) {
                result.emplace_back(current->value);
                aux->right = current;
                current = current->left;
            } else {
                aux->right = nullptr;
                current = current->right;
            }
        }
        return result;
    }
};
