#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class TreeNode:
    def __init__(self, value: int):
        self.value, self.left, self.right = value, None, None

class PreOrderTraversal:
    def traversal(self, root: TreeNode) -> List[int]:
        result, stack, current = [], [], root
        while current or stack:
            while current:
                result.append(current.value)

                stack.append(current)
                current = current.left
            current = stack.pop().right
        return result
