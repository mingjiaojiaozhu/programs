#!/usr/bin/env python
# -*- coding:gbk -*-

import math, sys

class FibonacciHeap:
    def __init__(self):
        self.__root, self.__length = None, 0

    def isEmpty(self) -> bool:
        return not self.__root

    def add(self, value: int) -> None:
        if self.__search(self.__root, value):
            return

        if not self.__root:
            self.__root = self.__TreeNode(value)
            self.__root.left, self.__root.right = self.__root, self.__root
        else:
            node = self.__TreeNode(value)
            self.__addNode(node, self.__root)
            if value < self.__root.value:
                self.__root = node
        self.__length += 1

    def erase(self, value: int) -> None:
        node = self.__search(self.__root, value)
        if not node:
            return

        if value != self.__root.value:
            node.value = self.__root.value - 1
            self.__decrease(node)

        current = self.__root
        while current.child:
            child = current.child
            self.__eraseNode(child)
            current.child = child.right if child.right != child else None
            self.__addNode(child, self.__root)
            child.parent = None

        self.__eraseNode(current)
        self.__root = current.right if current.right != current else None
        if current.right != current:
            self.__combine()
        self.__length -= 1

    def set(self, target: int, value: int) ->None:
        node = self.__search(self.__root, target)
        if node and target != value and not self.__search(self.__root, value):
            node.value = value
            if target < value:
                self.__increase(node)
            else:
                self.__decrease(node)

    def getRoot(self) -> int:
        if self.__root:
            return self.__root.value
        return -sys.maxsize

    def contains(self, value: int) -> bool:
        return bool(self.__search(self.__root, value))

    def clear(self) -> None:
        self.__root, self.__length = None, 0

    def __combine(self) -> None:
        maxDegree = math.ceil(math.log(self.__length) / math.log(2))
        heads = [None for _ in range(maxDegree + 1)]

        while self.__root:
            current = self.__root
            if current == current.right:
                self.__root = None
            else:
                self.__eraseNode(current)
                self.__root = current.right
            current.left, current.right = current, current

            degree = current.degree
            while heads[degree]:
                node = heads[degree]
                if current.value > node.value:
                    current, node = node, current

                self.__link(node, current)
                heads[degree] = None
                degree += 1
            heads[degree] = current

        for head in heads:
            if not head:
                continue

            if not self.__root:
                self.__root = head
            else:
                self.__addNode(head, self.__root)
                if head.value < self.__root.value:
                    self.__root = head

    def __search(self, node: '__TreeNode', value: int) -> '__TreeNode':
        if not node:
            return None

        current, flag = node, True
        while flag or current != node:
            flag = False
            if current.value == value:
                return current

            child = self.__search(current.child, value)
            if child:
                return child
            current = current.right
        return None

    def __increase(self, node: '__TreeNode') -> None:
        while node.child:
            child = node.child
            self.__eraseNode(child)
            if child.right == child:
                node.child = None
            else:
                node.child = child.right

            self.__addNode(child, self.__root)
            child.parent = None
        node.degree = 0

        parent = node.parent
        if parent:
            self.__cut(node, parent)
            self.__cascadingCut(parent)
        elif self.__root == node:
            right = node.right
            while right != node:
                if node.value > right.value:
                    self.__root = right
                right = right.right

    def __decrease(self, node: '__TreeNode') -> None:
        parent = node.parent
        if parent and node.value < parent.value:
            self.__cut(node, parent)
            self.__cascadingCut(parent)

        if node.value < self.__root.value:
            self.__root = node

    def __link(self, parent: '__TreeNode', child: '__TreeNode') -> None:
        self.__eraseNode(parent)
        if not child.child:
            child.child = parent
        else:
            self.__addNode(parent, child.child)

        parent.parent, parent.marked = child, False
        child.degree += 1

    def __addNode(self, node1: '__TreeNode', node2: '__TreeNode') -> None:
        node2.left.right, node1.left, node1.right, node2.left = node1, node2.left, node2, node1

    def __eraseNode(self, node: '__TreeNode') -> None:
        node.left.right, node.right.left = node.right, node.left

    def __cut(self, node: '__TreeNode', parent: '__TreeNode') -> None:
        self.__eraseNode(node)
        self.__setDegree(parent, node.degree)
        parent.child = node.right if node != node.right else None

        node.parent, node.left, node.right, node.marked = None, node, node, False
        self.__addNode(node, self.__root)

    def __cascadingCut(self, node: '__TreeNode') -> None:
        parent = node.parent
        if parent:
            if not node.marked:
                node.marked = True
            else:
                self.__cut(node, parent)
                self.__cascadingCut(parent)

    def __setDegree(self, parent: '__TreeNode', degree: int) -> None:
        parent.degree -= degree
        if parent.parent:
            self.__setDegree(parent.parent, degree)

    class __TreeNode:
        def __init__(self, value: int):
            self.value, self.degree, self.child, self.parent, self.left, self.right, self.marked = value, 0, None, None, None, None, False
