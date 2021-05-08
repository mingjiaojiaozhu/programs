#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class TreeNode:
    def __init__(self, value: int):
        self.value, self.left, self.right = value, None, None

class PostOrderTraversal:
    def traversal(self, root: TreeNode) -> List[int]:
        result, current = [], root
        while current:
            if not current.left:
                current = current.right
                continue

            aux = current.left
            while aux.right and aux.right != current:
                aux = aux.right
            if not aux.right:
                aux.right, current = current, current.left
            else:
                aux.right = None
                self.__traversal(current.left, result)
                current = current.right
        self.__traversal(root, result)
        return result

    def __traversal(self, parent: TreeNode, result: List[int]) -> None:
        tail = self.__reverse(parent)
        current = tail
        while current:
            result.append(current.value)
            current = current.right
        self.__reverse(tail)

    def __reverse(self, current: TreeNode) -> TreeNode:
        prev = None
        while current:
            next = current.right
            current.right, prev, current = prev, current, next
        return prev
