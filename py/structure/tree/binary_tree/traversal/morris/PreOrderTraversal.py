#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class TreeNode:
    def __init__(self, value: int):
        self.value, self.left, self.right = value, None, None

class PreOrderTraversal:
    def traversal(self, root: TreeNode) -> List[int]:
        result, current = [], root
        while current:
            if not current.left:
                result.append(current.value)
                current = current.right
                continue

            aux = current.left
            while aux.right and aux.right != current:
                aux = aux.right
            if not aux.right:
                result.append(current.value)
                aux.right, current = current, current.left
            else:
                aux.right, current = None, current.right
        return result
