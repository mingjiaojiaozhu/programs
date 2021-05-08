#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class DoublyLinkedList:
    def __init__(self):
        self.__head, self.__tail = self.__ListNode(0), self.__ListNode(0)
        self.__head.next, self.__tail.prev = self.__tail, self.__head

    def isEmpty(self) -> bool:
        return self.__head.next == self.__tail

    def add(self, index: int, value: int) ->None:
        current, count = self.__head, 0
        while current != self.__tail and count < index:
            current = current.next
            count += 1

        if current != self.__tail and count <= index:
            node = self.__ListNode(value)
            node.next, node.prev, current.next.prev, current.next = current.next, current, node, node

    def addHead(self, value: int) -> None:
        node = self.__ListNode(value)
        node.next, node.prev, self.__head.next.prev, self.__head.next = self.__head.next, self.__head, node, node

    def addTail(self, value: int) -> None:
        node = self.__ListNode(value)
        node.prev, node.next, self.__tail.prev.next, self.__tail.prev = self.__tail.prev, self.__tail, node, node

    def erase(self, index: int) -> None:
        current, count = self.__head, 0
        while current.next != self.__tail and count < index:
            current = current.next
            count += 1

        if current.next != self.__tail and count <= index:
            current.next.next.prev, current.next = current, current.next.next

    def eraseHead(self) -> None:
        if self.__head.next != self.__tail:
            self.__head.next.next.prev, self.__head.next = self.__head, self.__head.next.next

    def eraseTail(self) -> None:
        if self.__head.next != self.__tail:
            self.__tail.prev.prev.next, self.__tail.prev = self.__tail, self.__tail.prev.prev

    def set(self, index: int, value: int) -> None:
        current, count = self.__head.next, 0
        while current and count < index:
            current = current.next
            count += 1

        if current != self.__tail and count <= index:
            current.value = value

    def get(self, index: int) -> int:
        current, count = self.__head.next, 0
        while current and count < index:
            current = current.next
            count += 1

        if current != self.__tail and count <= index:
            return current.value
        return -sys.maxsize

    def clear(self) -> None:
        self.__head.next, self.__tail.prev = self.__tail, self.__head

    class __ListNode:
        def __init__(self, value: int):
            self.value, self.prev, self.next = value, None, None
