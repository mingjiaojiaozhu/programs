#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class BinarySearchTree:
    def __init__(self):
        self.__root = None

    def isEmpty(self) -> bool:
        return not self.__root

    def add(self, key: int, value: int) -> None:
        if not self.__root:
            self.__root = self.__TreeNode(key, value)
            return

        parent, current = None, self.__root
        while current:
            if key == current.key:
                current.value = value
                return

            parent = current
            if key < current.key:
                current = current.left
            else:
                current = current.right
        self.__addNode(parent, key, value)

    def erase(self, key: int) -> None:
        if not self.__root:
            return

        if key == self.__root.key and (not self.__root.left or not self.__root.right):
            self.__root = self.__root.left if self.__root.left else self.__root.right
            return

        parent, current = None, self.__root
        while current:
            if key == current.key:
                break

            parent = current
            if key < current.key:
                current = current.left
            else:
                current = current.right

        if not current:
            return

        if not current.left or not current.right:
            self.__eraseNode(parent, current, current.left if current.left else current.right)
            return

        child, parent = current.right, current
        while child.left:
            parent, child = child, child.left
        current.key, current.value = child.key, child.value
        self.__eraseNode(parent, child, child.right)

    def set(self, key: int, value: int) -> None:
        current = self.__root
        while current:
            if key == current.key:
                current.value = value
                return

            if key < current.key:
                current = current.left
            else:
                current = current.right

    def get(self, key: int) -> int:
        current = self.__root
        while current:
            if key == current.key:
                return current.value

            if key < current.key:
                current = current.left
            else:
                current = current.right
        return -sys.maxsize

    def clear(self) -> None:
        self.__root = None

    def __addNode(self, parent: '__TreeNode', key: int, value: int) -> None:
        if key < parent.key:
            parent.left = self.__TreeNode(key, value)
        else:
            parent.right = self.__TreeNode(key, value)

    def __eraseNode(self, parent: '__TreeNode', current: '__TreeNode', child: '__TreeNode') -> None:
        if current == parent.left:
            parent.left = child
        else:
            parent.right = child

    class __TreeNode:
        def __init__(self, key: int, value: int):
            self.key, self.value, self.left, self.right = key, value, None, None
