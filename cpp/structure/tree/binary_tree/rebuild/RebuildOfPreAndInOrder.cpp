#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
};

class RebuildOfPreAndInOrder {
public:
    TreeNode *rebuild(const vector<int> &preOrder, const vector<int> &inOrder) {
        int pivot = preOrder[0];
        TreeNode *parent = new TreeNode(pivot);
        if (1 == preOrder.size()) {
            return parent;
        }

        int index = 0;
        while (index < (int) preOrder.size() && pivot != inOrder[index]) {
            ++index;
        }

        if (index > 0) {
            parent->left = rebuild(vector<int>(preOrder.begin() + 1, preOrder.begin() + index + 1), vector<int>(inOrder.begin(), inOrder.begin() + index));
        }
        if (index < (int) preOrder.size() - 1) {
            parent->right = rebuild(vector<int>(preOrder.begin() + index + 1, preOrder.end()), vector<int>(inOrder.begin() + index + 1, inOrder.end()));
        }
        return parent;
    }
};
