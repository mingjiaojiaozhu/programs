#!/usr/bin/env python
# -*- coding:gbk -*-

import random, sys

class SkipList:
    def __init__(self):
        self.__head, self.__maxLevel = self.__ListNode(0), 1

    def isEmpty(self) -> bool:
        return not self.__head.next[0]

    def add(self, value: int) -> None:
        num, level = random.randrange(0, 65536), 0
        while num:
            level += 1
            num &= num - 1

        next = [self.__head for _ in range(level)]
        for i in range(level - 1, -1, -1):
            current = self.__head
            while current.next[i] and value > current.next[i].value:
                current = current.next[i]

            if current.next[i] and value == current.next[i].value:
                return
            next[i] = current

        node = self.__ListNode(value)
        for i in range(level):
            node.next[i] = next[i].next[i]
            next[i].next[i] = node

        if self.__maxLevel < level:
            self.__maxLevel = level

    def erase(self, value: int) -> None:
        next, current = [None for _ in range(self.__maxLevel)], self.__head
        for i in range(self.__maxLevel - 1, -1, -1):
            while current.next[i] and value > current.next[i].value:
                current = current.next[i]
            next[i] = current

        if not current.next[0] or value != current.next[0].value:
            return

        for i in range(self.__maxLevel - 1, -1, -1):
            if next[i].next[i] and value == next[i].next[i].value:
                next[i].next[i] = next[i].next[i].next[i]

        for i in range(self.__maxLevel - 1, -1, -1):
            if self.__head.next[i]:
                break
            self.__maxLevel -= 1

    def contains(self, value: int) -> bool:
        current = self.__head
        for i in range(self.__maxLevel - 1, -1, -1):
            while current.next[i] and value > current.next[i].value:
                current = current.next[i]
        return bool(current.next[0]) and value == current.next[0].value

    def clear(self) -> None:
        self.__head.next, self.__maxLevel = [None for _ in range(16)], 1

    class __ListNode:
        def __init__(self, value: int):
            self.value, self.next = value, [None for _ in range(16)]
