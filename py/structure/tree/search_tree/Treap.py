#!/usr/bin/env python
# -*- coding:gbk -*-

import random, sys

class Treap:
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
            if parent.factor < parent.left.factor:
                parent = self.__rightRotation(parent)
        else:
            parent.right = self.__addNode(parent.right, key, value)
            if parent.factor < parent.right.factor:
                parent = self.__leftRotation(parent)
        return parent

    def __eraseNode(self, parent: '__TreeNode', key: int) -> '__TreeNode':
        if not parent:
            return None

        if key == parent.key:
            if parent.left and parent.right:
                if parent.left.factor > parent.right.factor:
                    parent = self.__rightRotation(parent)
                    parent.right = self.__eraseNode(parent.right, key)
                else:
                    parent = self.__leftRotation(parent)
                    parent.left = self.__eraseNode(parent.left, key)
            else:
                parent = parent.left if parent.left else parent.right
        elif key < parent.key:
            parent.left = self.__eraseNode(parent.left, key)
        else:
            parent.right = self.__eraseNode(parent.right, key)
        return parent

    def __leftRotation(self, current: '__TreeNode') -> '__TreeNode':
        child = current.right
        current.right, child.left = child.left, current
        return child

    def __rightRotation(self, current: '__TreeNode') -> '__TreeNode':
        child = current.left
        current.left, child.right = child.right, current
        return child

    class __TreeNode:
        def __init__(self, key: int, value: int):
            self.key, self.value, self.factor, self.left, self.right = key, value, random.randrange(0, 65536), None, None
