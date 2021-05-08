#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class QueueOfLinkedList:
    def __init__(self):
        self.__head, self.__tail = self.__ListNode(0), self.__ListNode(0)
        self.__head.next, self.__tail.prev = self.__tail, self.__head

    def isEmpty(self) -> bool:
        return self.__head.next == self.__tail

    def enqueue(self, value: int) -> None:
        node = self.__ListNode(value)
        node.prev, node.next, self.__tail.prev.next, self.__tail.prev = self.__tail.prev, self.__tail, node, node

    def dequeue(self) -> int:
        if self.__head.next != self.__tail:
            node = self.__head.next
            node.next.prev, self.__head.next = self.__head, node.next
            return node.value
        return -sys.maxsize

    def clear(self) -> None:
        self.__head.next, self.__tail.prev = self.__tail, self.__head

    class __ListNode:
        def __init__(self, value: int):
            self.value, self.prev, self.next = value, None, None
