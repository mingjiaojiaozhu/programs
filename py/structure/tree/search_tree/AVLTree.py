#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class AVLTree:
    def __init__(self):
        self.__root = None

    def isEmpty(self) -> bool:
        return not self.__root

    def add(self, key: int, value: int) -> None:
        self.__root = self.__addNode(self.__root, key, value)

    def erase(self, key: int) -> None:
        self.__root = self.__eraseNode(self.__root, key)

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

    def __addNode(self, parent: '__TreeNode', key: int, value: int) -> '__TreeNode':
        if not parent:
            return self.__TreeNode(key, value)

        if key == parent.key:
            parent.value = value
            return parent

        if key < parent.key:
            parent.left = self.__addNode(parent.left, key, value)
            if self.__getHeight(parent.left) - self.__getHeight(parent.right) >= 2:
                if key < parent.left.key:
                    parent = self.__leftLeftRotation(parent)
                else:
                    parent = self.__leftRightRotation(parent)
        else:
            parent.right = self.__addNode(parent.right, key, value)
            if self.__getHeight(parent.right) - self.__getHeight(parent.left) >= 2:
                if key > parent.right.key:
                    parent = self.__rightRightRotation(parent)
                else:
                    parent = self.__rightLeftRotation(parent)
        parent.height = max(self.__getHeight(parent.left), self.__getHeight(parent.right)) + 1
        return parent

    def __eraseNode(self, parent: '__TreeNode', key: int) -> '__TreeNode':
        if not parent:
            return None

        if key == parent.key:
            if parent.left and parent.right:
                current = parent.right
                while current:
                    current = current.left
                parent.key, parent.value = current.key, current.value
                parent.right = self.__eraseNode(parent.right, key)
            else:
                parent = parent.left if parent.left else parent.right
        elif key < parent.key:
            parent.left = self.__eraseNode(parent.left, key)
            if self.__getHeight(parent.right) - self.__getHeight(parent.left) >= 2:
                if self.__getHeight(parent.right.right) > self.__getHeight(parent.right.left):
                    parent = self.__rightRightRotation(parent)
                else:
                    parent = self.__rightLeftRotation(parent)
        else:
            parent.right = self.__eraseNode(parent.right, key)
            if self.__getHeight(parent.left) - self.__getHeight(parent.right) >= 2:
                if self.__getHeight(parent.left.right) < self.__getHeight(parent.left.left):
                    parent = self.__leftLeftRotation(parent)
                else:
                    parent = self.__leftRightRotation(parent)

        if parent:
            parent.height = max(self.__getHeight(parent.left), self.__getHeight(parent.right)) + 1
        return parent

    def __getHeight(self, current: '__TreeNode') -> int:
        if not current:
            return 0
        return current.heigh

    def __leftLeftRotation(self, current: '__TreeNode') -> '__TreeNode':
        child = current.left
        current.left, child.right = child.right, current

        current.height = max(self.__getHeight(current.left), self.__getHeight(current.right)) + 1
        child.height = max(self.__getHeight(child.left), self.__getHeight(child.right)) + 1
        return child

    def __rightRightRotation(self, current: '__TreeNode') -> '__TreeNode':
        child = current.right
        current.right, child.left = child.left, current

        current.height = max(self.__getHeight(current.left), self.__getHeight(current.right)) + 1
        child.height = max(self.__getHeight(child.left), self.__getHeight(child.right)) + 1
        return child

    def __leftRightRotation(self, current: '__TreeNode') -> '__TreeNode':
        current.left = self.__rightRightRotation(current.left)
        return self.__leftLeftRotation(current)

    def __rightLeftRotation(self, current: '__TreeNode') -> '__TreeNode':
        current.left = self.__leftLeftRotation(current.left)
        return self.__rightRightRotation(current)

    class __TreeNode:
        def __init__(self, key: int, value: int):
            self.key, self.value, self.heigh, self.left, self.right = key, value, 1, None, None
