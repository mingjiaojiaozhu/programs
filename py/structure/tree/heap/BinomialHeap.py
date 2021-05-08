#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class BinomialHeap:
    def __init__(self):
        self.__root = None

    def isEmpty(self) -> bool:
        return not self.__root

    def add(self, value: int) -> None:
        if not self.__search(self.__root, value):
            self.__root = self.__TreeNode(value) if not self.__root else self.__combine(self.__root, self.__TreeNode(value))

    def erase(self, value: int) -> None:
        node = self.__search(self.__root, value)
        if not node:
            return

        parent = node.parent
        while parent:
            node.value, parent.value = parent.value, node.value
            node, parent = parent, node.parent

        pivot, current = None, self.__root
        while current != node:
            pivot, current = current, current.next

        if pivot:
            pivot.next = node.next
        else:
            self.__root = node.next
        self.__root = self.__combine(self.__root, self.__reverse(node.child))

    def set(self, target: int, value: int) ->None:
        node = self.__search(self.__root, target)
        if node and target != value and not self.__search(self.__root, value):
            node.value = value
            if target < value:
                self.__increase(node)
            else:
                self.__decrease(node)

    def getRoot(self) -> int:
        if not self.__root:
            return -sys.maxsize

        pivot, current = self.__root, self.__root.next
        while current:
            if pivot.value > current.value:
                pivot = current
            current = current.next
        return pivot.value

    def contains(self, value: int) -> bool:
        return bool(self.__search(self.__root, value))

    def clear(self) -> None:
        self.__root = None

    def __combine(self, node1: '__TreeNode', node2: '__TreeNode') -> '__TreeNode':
        head = self.__merge(node1, node2)
        if not head:
            return head

        parent, current = None, head
        while current.next:
            next = current.next
            if (current.degree != next.degree) or (next.next and next.degree == next.next.degree):
                parent, current = current, next
            elif current.value <= next.value:
                current.next = next.next
                self.__link(current, next)
            else:
                if not parent:
                    head = next
                else:
                    parent.next = next
                self.__link(next, current)
                current = next
        return head

    def __merge(self, node1: '__TreeNode', node2: '__TreeNode') -> '__TreeNode':
        if not node1 or not node2:
            return node1 if node1 else node2

        parent, head = None, None
        while node1 and node2:
            if node1.degree <= node2.degree:
                pivot, node1 = node1, node1.next
            else:
                pivot, node2 = node2, node2.next

            if not parent:
                parent, head = pivot, pivot
            else:
                parent.next, parent = pivot, pivot
            pivot.next = node1 if node1 else node2
        return head

    def __reverse(self, node: '__TreeNode') -> '__TreeNode':
        if not node:
            return node

        node.parent, tail = None, None
        while node.next:
            next = node.next
            node.next, tail, node = tail, node, next
            node.parent = None
        node.next = tail
        return node

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
        child = node.child
        while child:
            if node.value < child.value:
                child = child.next
                continue

            pivot = child
            while child.next:
                if child.next.value < pivot.value:
                    pivot = child.next
                child = child.next
            node.value, pivot.value = pivot.value, node.value
            node, child = pivot, node.child

    def __decrease(self, node: '__TreeNode') -> None:
        parent = node.parent
        while parent and node.value < parent.value:
            node.value, parent.value = parent.value, node.value
            node, parent = parent, node.parent

    def __link(self, parent: '__TreeNode', child: '__TreeNode') -> '__TreeNode':
        child.parent, child.next, parent.child = parent, parent.child, child
        parent.degree += 1

    class __TreeNode:
        def __init__(self, value: int):
            self.value, self.degree, self.child, self.parent, self.next = value, 0, None, None, None
