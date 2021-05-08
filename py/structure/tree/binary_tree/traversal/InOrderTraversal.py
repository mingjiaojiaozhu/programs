#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class TreeNode:
    def __init__(self, value: int):
        self.value, self.left, self.right = value, None, None

class InOrderTraversal:
    def traversal(self, root: TreeNode) -> List[int]:
        result, stack, current = [], [], root
        while current or stack:
            while current:
                stack.append(current)
                current = current.left

            current = stack.pop()
            result.append(current.value)

            current = current.right
        return result
