#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class TreeNode:
    def __init__(self, value: int):
        self.value, self.left, self.right = value, None, None

class RebuildOfInAndPostOrder:
    def rebuild(self, inOrder: List[int], postOrder: List[int]) -> TreeNode:
        pivot = postOrder[-1]
        parent = TreeNode(pivot)
        if 1 == len(postOrder):
            return parent

        index = 0
        while index < len(postOrder) and pivot != inOrder[index]:
            index += 1

        if index > 0:
            parent.left = self.rebuild(inOrder[ : index], postOrder[ : index])
        if index < len(postOrder) - 1:
            parent.right = self.rebuild(inOrder[index + 1 : ], postOrder[index : -1])
        return parent
