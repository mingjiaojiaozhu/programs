#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class PairingHeap:
    def __init__(self):
        self.__root = None

    def isEmpty(self) -> bool:
        return not self.__root

    def add(self, value: int) -> None:
        if not self.__search(self.__root, value):
            self.__root = self.__TreeNode(value) if not self.__root else self.__merge(self.__root, self.__TreeNode(value))

    def erase(self, value: int) -> None:
        node = self.__search(self.__root, value)
        if not node:
            return

        if value != self.__root.value:
            node.value = self.__root.value - 1
            self.__decrease(node)

        current = self.__root
        if not current.child:
            self.__root = None
        else:
            child = current.child
            child.parent = None
            self.__root = self.__combine(child)

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
        self.__root = None

    def __merge(self, node1: '__TreeNode', node2: '__TreeNode') -> '__TreeNode':
        if not node1 or not node2:
            return node1 if node1 else node2

        if node1.value < node2.value:
            next = node2.next
            node1.next = next
            if next:
                next.parent = node1

            child = node1.child
            node2.parent, node2.next = node1, child
            if child:
                child.parent = node2
            node1.child = node2
            return node1

        parent = node1.parent
        node2.parent = parent
        if parent and parent.child != node1:
            parent.next = node2

        child = node2.child
        node1.parent, node1.next = node2, child
        if child:
            child.parent = node1
        node2.child = node1
        return node2

    def __combine(self, node: '__TreeNode') -> '__TreeNode':
        current = node
        next, tail = current.next, current

        flag = True
        while next:
            tail = self.__merge(current, next)
            current = tail.next
            next = current.next if current else None

            if not flag and not current:
                break
            flag = False

        if current:
            tail = current

        parent = tail.parent
        while parent:
            tail = self.__merge(parent, tail)
            parent = tail.parent
        return tail

    def __search(self, node: '__TreeNode', value: int) -> '__TreeNode':
        while node:
            if value == node.value:
                return node

            child = self.__search(node.child, value)
            if child:
                return child
            node = node.next
        return None

    def __increase(self, node: '__TreeNode') -> None:
        pivot = node.value
        while node.child and pivot < node.child.value:
            node.value = node.child.value
            node = node.child
        node.value = pivot

    def __decrease(self, node: '__TreeNode') -> None:
        parent = node.parent
        if parent.child == node:
            parent.child = node.next
        else:
            parent.next = node.next
        if node.next:
            node.next.parent = parent

        node.parent, node.next = None, None
        self.__root = self.__merge(node, self.__root)

    class __TreeNode:
        def __init__(self, value: int):
            self.value, self.child, self.parent, self.next = value, None, None, None
