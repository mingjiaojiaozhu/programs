#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class StackOfLinkedList:
    def __init__(self):
        self.__head = self.__ListNode(0)

    def isEmpty(self) -> bool:
        return not self.__head.next

    def push(self, value: int) -> None:
        node = self.__ListNode(value)
        node.next, self.__head.next = self.__head.next, node

    def pop(self) -> int:
        if self.__head.next:
            node = self.__head.next
            self.__head.next = node.next
            return node.value
        return -sys.maxsize

    def clear(self) -> None:
        self.__head.next = None

    class __ListNode:
        def __init__(self, value: int):
            self.value, self.next = value, None
