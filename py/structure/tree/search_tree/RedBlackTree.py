#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class RedBlackTree:
    def __init__(self):
        self.__red, self.__black = '0', '1'
        self.__root = None

    def isEmpty(self) -> bool:
        return not self.__root

    def add(self, key: int, value: int) -> None:
        if not self.__root:
            self.__root = self.__TreeNode(key, value, self.__black, None)
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
        child = self.__TreeNode(key, value, self.__red, parent)
        if key < parent.key:
            parent.left = child
        else:
            parent.right = child
        self.__addFixup(child)

    def __eraseNode(self, parent: '__TreeNode', current: '__TreeNode', child: '__TreeNode') -> None:
        color = current.color
        if current == parent.left:
            parent.left = child
        else:
            parent.right = child

        if child:
            child.parent = parent

        if self.__black == color:
            self.__eraseFixup(child, parent)

    def __addFixup(self, current: '__TreeNode') -> None:
        parent = current.parent
        while parent and self.__red == parent.color:
            grandParent = parent.parent
            if parent == grandParent.left:
                current = self.__addFixupNode(current, parent, grandParent, grandParent.right, parent.right, True)
            else:
                current = self.__addFixupNode(current, parent, grandParent, grandParent.left, parent.left, False)
            parent = current.parent
        self.__root.color = self.__black

    def __eraseFixup(self, current: '__TreeNode', parent: '__TreeNode') -> None:
        while (not current or self.__black == current.color) and current != self.__root:
            if parent.left == current:
                current = self.__eraseFixupNode(parent, parent.right, True)
            else:
                current = self.__eraseFixupNode(parent, parent.left, False)
            parent = current.parent

        if current:
            current.color = self.__black

    def __addFixupNode(self, current: '__TreeNode', parent: '__TreeNode', grandParent: '__TreeNode', uncle: '__TreeNode', brother: '__TreeNode', isLeft: bool) -> '__TreeNode':
        if uncle and self.__red == uncle.color:
            uncle.color, parent.color, grandParent.color = self.__black, self.__black, self.__red
            return grandParent

        if brother == current:
            if isLeft:
                self.__leftRotation(parent)
            else:
                self.__rightRotation(parent)
            parent, current = current, parent

        parent.color, grandParent.color = self.__black, self.__red
        if isLeft:
            self.__rightRotation(grandParent)
        else:
            self.__leftRotation(grandParent)
        return current

    def __eraseFixupNode(self, parent: '__TreeNode', brother: '__TreeNode', isLeft: bool) -> '__TreeNode':
        if self.__red == brother.color:
            brother.color, parent.color = self.__black, self.__red

            if isLeft:
                self.__leftRotation(parent)
                brother = parent.right
            else:
                self.__rightRotation(parent)
                brother = parent.left

        if (not brother.left or self.__black == brother.left.color) and (not brother.right or self.__black == brother.right.color):
            brother.color = self.__red
            return parent

        if isLeft and (not brother.right or self.__black == brother.right.color):
            brother.left.color, brother.color = self.__black, self.__red
            self.__rightRotation(brother)
            brother = parent.right
        if not isLeft and (not brother.left or self.__black == brother.left.color):
            brother.right.color, brother.color = self.__black, self.__red
            self.__leftRotation(brother)
            brother = parent.left

        brother.color, parent.color = parent.color, self.__black
        if isLeft:
            brother.right.color = self.__black
            self.__leftRotation(parent)
        else:
            brother.left.color = self.__black
            self.__rightRotation(parent)
        return self.__root

    def __leftRotation(self, current: '__TreeNode') -> None:
        child = current.right
        current.right = child.left
        if child.left:
            child.left.parent = current
        child.parent = current.parent

        if not current.parent:
            self.__root = child
        else:
            if current.parent.left == current:
                current.parent.left = child
            else:
                current.parent.right = child
        child.left, current.parent = current, child

    def __rightRotation(self, current: '__TreeNode') -> None:
        child = current.left
        current.left = child.right
        if child.right:
            child.right.parent = current
        child.parent = current.parent

        if not current.parent:
            self.__root = child
        else:
            if current.parent.left == current:
                current.parent.left = child
            else:
                current.parent.right = child
        child.right, current.parent = current, child

    class __TreeNode:
        def __init__(self, key: int, value: int, color: str, parent: '__TreeNode'):
            self.key, self.value, self.color, self.left, self.right, self.parent = key, value, color, None, None, parent
