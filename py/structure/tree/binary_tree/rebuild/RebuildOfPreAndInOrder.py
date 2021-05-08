#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class TreeNode:
    def __init__(self, value: int):
        self.value, self.left, self.right = value, None, None

class RebuildOfPreAndInOrder:
    def rebuild(self, preOrder: List[int], inOrder: List[int]) -> TreeNode:
        pivot = preOrder[0]
        parent = TreeNode(pivot)
        if 1 == len(preOrder):
            return parent

        index = 0
        while index < len(preOrder) and pivot != inOrder[index]:
            index += 1

        if index > 0:
            parent.left = self.rebuild(preOrder[1 : index + 1], inOrder[ : index])
        if index < len(preOrder) - 1:
            parent.right = self.rebuild(preOrder[index + 1 : ], inOrder[index + 1 : ])
        return parent
