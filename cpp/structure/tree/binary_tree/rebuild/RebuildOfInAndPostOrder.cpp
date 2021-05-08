#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
};

class RebuildOfInAndPostOrder {
public:
    TreeNode *rebuild(const vector<int> &inOrder, const vector<int> &postOrder) {
        int pivot = postOrder[postOrder.size() - 1];
        TreeNode *parent = new TreeNode(pivot);
        if (1 == postOrder.size()) {
            return parent;
        }

        int index = 0;
        while (index < (int) postOrder.size() && pivot != inOrder[index]) {
            ++index;
        }

        if (index > 0) {
            parent->left = rebuild(vector<int>(inOrder.begin(), inOrder.begin() + index), vector<int>(postOrder.begin(), postOrder.begin() + index));
        }
        if (index < (int) postOrder.size() - 1) {
            parent->right = rebuild(vector<int>(inOrder.begin() + index + 1, inOrder.end()), vector<int>(postOrder.begin() + index, postOrder.end() - 1));
        }
        return parent;
    }
};
