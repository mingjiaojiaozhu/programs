#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class HashOfChainAddress:
    def __init__(self):
        self.__hash = [self.__HashNode(0, 0) for _ in range(64)]

    def isEmpty(self) -> bool:
        for node in self.__hash:
            if node.next:
                return False
        return True

    def add(self, key: int, value: int) -> None:
        current = self.__hash[key % 64]
        while current.next:
            current = current.next
            if key == current.key:
                current.value = value
                return
        current.next = self.__HashNode(key, value)

    def erase(self, key: int) -> None:
        current = self.__hash[key % 64]
        while current.next:
            if key == current.next.key:
                current.next = current.next.next
                return
            current = current.next

    def set(self, key: int, value: int) -> None:
        current = self.__hash[key % 64].next
        while current and key != current.key:
            current = current.next

        if current:
            current.value = value

    def get(self, key: int) -> int:
        current = self.__hash[key % 64].next
        while current and key != current.key:
            current = current.next

        if current:
            return current.value
        return -sys.maxsize

    def clear(self) -> None:
        for node in self.__hash:
            node.next = None

    class __HashNode:
        def __init__(self, key: int, value: int):
            self.key, self.value, self.next = key, value, None
