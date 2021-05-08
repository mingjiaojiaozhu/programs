#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int start;
    int end;
    int value;
    int covered;
} TreeNode;

typedef TreeNode *pNode;

typedef struct {
    pNode *arrays;
    int length;
} SegmentTreeNode;

static void createNode(SegmentTreeNode *tree, int *nums, int start, int end, int parent);
static void setNode(SegmentTreeNode *tree, int index, int value, int parent);
static void setNodes(SegmentTreeNode *tree, int start, int end, int value, int parent);
static int getNodes(SegmentTreeNode tree, int start, int end, int parent);

void create(SegmentTreeNode *tree, int *nums, int length) {
    tree->arrays = (pNode *) malloc(sizeof(pNode) * (length << 2));
    for (int i = 0; i < (length << 2); ++i) {
        tree->arrays[i] = (pNode) malloc(sizeof(TreeNode));
        tree->arrays[i]->start = 0;
        tree->arrays[i]->end = 0;
        tree->arrays[i]->value = 0;
        tree->arrays[i]->covered = 0;
    }
    tree->length = length;
    createNode(tree, nums, 0, length - 1, 0);
}

void set(SegmentTreeNode *tree, int index, int value) {
    if (index >= 0 && index < tree->length) {
        setNode(tree, index, value, 0);
    }
}

void setInterval(SegmentTreeNode *tree, int start, int end, int value) {
    if (start >= 0 && start < tree->length && end >= 0 && end < tree->length) {
        setNodes(tree, start, end, value, 0);
    }
}

int get(SegmentTreeNode tree, int index) {
    if (index >= 0 && index < tree.length) {
        return getNodes(tree, index, index, 0);
    }
    return 1 << 31;
}

int getInterval(SegmentTreeNode tree, int start, int end) {
    if (start >= 0 && start < tree.length && end >= 0 && end < tree.length) {
        return getNodes(tree, start, end, 0);
    }
    return 1 << 31;
}

static void createNode(SegmentTreeNode *tree, int *nums, int start, int end, int parent) {
    tree->arrays[parent]->start = start;
    tree->arrays[parent]->end = end;
    if (start == end) {
        tree->arrays[parent]->value = nums[start];
        return;
    }

    int middle = start + ((end - start) >> 1);
    int child = (parent << 1) + 1;
    createNode(tree, nums, start, middle, child);
    createNode(tree, nums, middle + 1, end, child + 1);
    tree->arrays[parent]->value = tree->arrays[child]->value + tree->arrays[child + 1]->value;
}

static void setNode(SegmentTreeNode *tree, int index, int value, int parent) {
    if (tree->arrays[parent]->start == tree->arrays[parent]->end) {
        tree->arrays[parent]->value = value;
        return;
    }

    int middle = tree->arrays[parent]->start + ((tree->arrays[parent]->end - tree->arrays[parent]->start) >> 1);
    int child = (parent << 1) + 1;
    if (index <= middle) {
        setNode(tree, index, value, child);
    } else {
        setNode(tree, index, value, child + 1);
    }
    tree->arrays[parent]->value = tree->arrays[child]->value + tree->arrays[child + 1]->value;
}

static void setNodes(SegmentTreeNode *tree, int start, int end, int value, int parent) {
    if (start == tree->arrays[parent]->start && end == tree->arrays[parent]->end) {
        tree->arrays[parent]->value += (end - start + 1) * value;
        tree->arrays[parent]->covered += value;
        return;
    }

    int middle = tree->arrays[parent]->start + ((tree->arrays[parent]->end - tree->arrays[parent]->start) >> 1);
    int child = (parent << 1) + 1;
    if (end <= middle) {
        setNodes(tree, start, end, value, child);
    } else if (start > middle) {
        setNodes(tree, start, end, value, child + 1);
    } else {
        setNodes(tree, start, middle, value, child);
        setNodes(tree, middle + 1, end, value, child + 1);
    }
    tree->arrays[parent]->value = tree->arrays[child]->value + tree->arrays[child + 1]->value;
}

static int getNodes(SegmentTreeNode tree, int start, int end, int parent) {
    if (tree.arrays[parent]->covered) {
        if (tree.arrays[parent]->start != tree.arrays[parent]->end) {
            int child = (parent << 1) + 1;
            int covered = tree.arrays[parent]->covered;
            tree.arrays[child]->covered += covered;
            tree.arrays[child + 1]->covered += covered;
            if (covered) {
                tree.arrays[child]->value += (tree.arrays[child]->end - tree.arrays[child]->start + 1) * covered;
                tree.arrays[child + 1]->value += (tree.arrays[child + 1]->end - tree.arrays[child + 1]->start + 1) * covered;
            }
        }
        tree.arrays[parent]->covered = 0;
    }

    if (start == tree.arrays[parent]->start && end == tree.arrays[parent]->end) {
        return tree.arrays[parent]->value;
    }

    int middle = tree.arrays[parent]->start + ((tree.arrays[parent]->end - tree.arrays[parent]->start) >> 1);
    int child = (parent << 1) + 1;
    if (end <= middle) {
        return getNodes(tree, start, end, child);
    }
    if (start > middle) {
        return getNodes(tree, start, end, child + 1);
    }
    return getNodes(tree, start, middle, child) + getNodes(tree, middle + 1, end, child + 1);
}
