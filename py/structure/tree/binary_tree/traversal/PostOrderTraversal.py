#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class TreeNode:
    def __init__(self, value: int):
        self.value, self.left, self.right = value, None, None

class PostOrderTraversal:
    def traversal(self, root: TreeNode) -> List[int]:
        result, stack, current = [], [root], None
        while stack:
            aux = stack[-1]
            if aux.left and current != aux.left and current != aux.right:
                stack.append(aux.left)
            elif aux.right and current != aux.right:
                stack.append(aux.right)
            else:
                result.append(aux.value)
                current = aux
                stack.pop()
        return result
