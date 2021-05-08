#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class SplayTree:
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
        current = self.__addNode(parent, key, value)
        self.__splay(current)

    def erase(self, key: int) -> None:
        if not self.__root:
            return

        if key == self.__root.key and (not self.__root.left or not self.__root.right):
            self.__root = self.__root.left if self.__root.left else self.__root.right
            return

        current = self.__root
        while current:
            if key == current.key:
                break

            if key < current.key:
                current = current.left
            else:
                current = current.right

        if not current:
            return

        self.__splay(current)
        if not current.left or not current.right:
            self.__root = current.left if current.left else current.right
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
                self.__splay(current)
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
                self.__splay(current)
                return current.value

            if key < current.key:
                current = current.left
            else:
                current = current.right
        return -sys.maxsize

    def clear(self) -> None:
        self.__root = None

    def __addNode(self, parent: '__TreeNode', key: int, value: int) -> '__TreeNode':
        child = self.__TreeNode(key, value)
        if key < parent.key:
            parent.left = child
        else:
            parent.right = child
        return child

    def __eraseNode(self, parent: '__TreeNode', current: '__TreeNode', child: '__TreeNode') -> None:
        if current == parent.left:
            parent.left = child
        else:
            parent.right = child

    def __splay(self, pivot: '__TreeNode') -> None:
        aux = self.__TreeNode(0, 0)
        left, right = aux, aux

        current = self.__root
        while pivot != current:
            if pivot.key < current.key:
                if pivot.key < current.left.key:
                    current = self.__leftRotation(current)
                right.left, right, current = current, current, current.left
            else:
                if pivot.key > current.right.key:
                    current = self.__rightRotation(current)
                left.right, left, current = current, current, current.right

        left.right, right.left = current.left, current.right
        current.left, current.right = aux.right, aux.left
        self.__root = current

    def __leftRotation(self, current: '__TreeNode') -> '__TreeNode':
        child = current.left
        current.left, child.right = child.right, current
        return child

    def __rightRotation(self, current: '__TreeNode') -> '__TreeNode':
        child = current.right
        current.right, child.left = child.left, current
        return child

    class __TreeNode:
        def __init__(self, key: int, value: int):
            self.key, self.value, self.left, self.right = key, value, None, None
