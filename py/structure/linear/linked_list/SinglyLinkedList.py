#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class SinglyLinkedList:
    def __init__(self):
        self.__head = self.__ListNode(0)

    def isEmpty(self) -> bool:
        return not self.__head.next

    def add(self, index: int, value: int) ->None:
        current, count = self.__head, 0
        while current and count < index:
            current = current.next
            count += 1

        if current and count <= index:
            node = self.__ListNode(value)
            node.next, current.next = current.next, node

    def addHead(self, value: int) -> None:
        node = self.__ListNode(value)
        node.next, self.__head.next = self.__head.next, node

    def addTail(self, value: int) -> None:
        current = self.__head
        while current.next:
            current = current.next

        node = self.__ListNode(value)
        node.next, current.next = None, node

    def erase(self, index: int) -> None:
        current, count = self.__head, 0
        while current.next and count < index:
            current = current.next
            count += 1

        if current.next and count <= index:
            current.next = current.next.next

    def eraseHead(self) -> None:
        if self.__head.next:
            self.__head.next = self.__head.next.next

    def eraseTail(self) -> None:
        if not self.__head.next:
            return

        current = self.__head
        while current.next.next:
            current = current.next
        current.next = None

    def set(self, index: int, value: int) -> None:
        current, count = self.__head.next, 0
        while current and count < index:
            current = current.next
            count += 1

        if current and count <= index:
            current.value = value

    def get(self, index: int) -> int:
        current, count = self.__head.next, 0
        while current and count < index:
            current = current.next
            count += 1

        if current and count <= index:
            return current.value
        return -sys.maxsize

    def reverse(self) -> None:
        prev, current = None, self.__head.next
        while current:
            next = current.next
            current.next, prev, current = prev, current, next
        self.__head.next = prev

    def clear(self) -> None:
        self.__head.next = None

    class __ListNode:
        def __init__(self, value: int):
            self.value, self.next = value, None
