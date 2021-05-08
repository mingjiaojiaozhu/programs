#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
public:
    SegmentTree(vector<int> &nums) {
        for (int i = 0; i < ((int) nums.size() << 2); ++i) {
            arrays.emplace_back(new TreeNode());
        }
        length = nums.size();
        createNode(nums, 0, nums.size() - 1, 0);
    }

    void set(int index, int value) {
        if (index >= 0 && index < length) {
            setNode(index, value, 0);
        }
    }

    void setInterval(int start, int end, int value) {
        if (start >= 0 && start < length && end >= 0 && end < length) {
            setNodes(start, end, value, 0);
        }
    }

    int get(int index) {
        if (index >= 0 && index < length) {
            return getNodes(index, index, 0);
        }
        return INT_MIN;
    }

    int getInterval(int start, int end) {
        if (start >= 0 && start < length && end >= 0 && end < length) {
            return getNodes(start, end, 0);
        }
        return INT_MIN;
    }

private:
    struct TreeNode {
        int start;
        int end;
        int value;
        int covered;

        TreeNode() : start(0), end(0), value(0), covered(0) {}
    };

    vector<TreeNode *> arrays;
    int length;

    void createNode(vector<int> &nums, int start, int end, int parent) {
        arrays[parent]->start = start;
        arrays[parent]->end = end;
        if (start == end) {
            arrays[parent]->value = nums[start];
            return;
        }

        int middle = start + ((end - start) >> 1);
        int child = (parent << 1) + 1;
        createNode(nums, start, middle, child);
        createNode(nums, middle + 1, end, child + 1);
        arrays[parent]->value = arrays[child]->value + arrays[child + 1]->value;
    }

    void setNode(int index, int value, int parent) {
        if (arrays[parent]->start == arrays[parent]->end) {
            arrays[parent]->value = value;
            return;
        }

        int middle = arrays[parent]->start + ((arrays[parent]->end - arrays[parent]->start) >> 1);
        int child = (parent << 1) + 1;
        if (index <= middle) {
            setNode(index, value, child);
        } else {
            setNode(index, value, child + 1);
        }
        arrays[parent]->value = arrays[child]->value + arrays[child + 1]->value;
    }

    void setNodes(int start, int end, int value, int parent) {
        if (start == arrays[parent]->start && end == arrays[parent]->end) {
            arrays[parent]->value += (end - start + 1) * value;
            arrays[parent]->covered += value;
            return;
        }

        int middle = arrays[parent]->start + ((arrays[parent]->end - arrays[parent]->start) >> 1);
        int child = (parent << 1) + 1;
        if (end <= middle) {
            setNodes(start, end, value, child);
        } else if (start > middle) {
            setNodes(start, end, value, child + 1);
        } else {
            setNodes(start, middle, value, child);
            setNodes(middle + 1, end, value, child + 1);
        }
        arrays[parent]->value = arrays[child]->value + arrays[child + 1]->value;
    }

    int getNodes(int start, int end, int parent) {
        if (arrays[parent]->covered) {
            if (arrays[parent]->start != arrays[parent]->end) {
                int child = (parent << 1) + 1;
                int covered = arrays[parent]->covered;
                arrays[child]->covered += covered;
                arrays[child + 1]->covered += covered;
                if (covered) {
                    arrays[child]->value += (arrays[child]->end - arrays[child]->start + 1) * covered;
                    arrays[child + 1]->value += (arrays[child + 1]->end - arrays[child + 1]->start + 1) * covered;
                }
            }
            arrays[parent]->covered = 0;
        }

        if (start == arrays[parent]->start && end == arrays[parent]->end) {
            return arrays[parent]->value;
        }

        int middle = arrays[parent]->start + ((arrays[parent]->end - arrays[parent]->start) >> 1);
        int child = (parent << 1) + 1;
        if (end <= middle) {
            return getNodes(start, end, child);
        }
        if (start > middle) {
            return getNodes(start, end, child + 1);
        }
        return getNodes(start, middle, child) + getNodes(middle + 1, end, child + 1);
    }
};
