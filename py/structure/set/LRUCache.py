#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class LRUCache:
    def __init__(self):
        self.__hash, self.__head, self.__tail = {}, self.__HashNode(0, 0), self.__HashNode(0, 0)
        self.__head.next, self.__tail.prev = self.__tail, self.__head

    def isEmpty(self) -> bool:
        return not self.__hash

    def set(self, key: int, value: int) -> None:
        if key in self.__hash:
            self.__erase(self.__hash[key])
            self.__hash[key] = self.__HashNode(key, value)
            self.__add(self.__hash[key])
            return

        if len(self.__hash) >= 64:
            node = self.__head.next
            self.__erase(node)
            del self.__hash[node.key]

        node = self.__HashNode(key, value)
        self.__hash[key] = node
        self.__add(node)

    def get(self, key: int) -> int:
        if key in self.__hash:
            node = self.__hash[key]
            self.__erase(node)
            self.__add(node)
            return node.value
        return -sys.maxsize

    def __add(self, node: '__HashNode') -> None:
        prev = self.__tail.prev
        node.prev, node.next, prev.next, self.__tail.prev = prev, self.__tail, node, node

    def __erase(self, node: '__HashNode') -> None:
        prev, next = node.prev, node.next
        prev.next, next.prev = next, prev

    def clear(self) -> None:
        self.__hash.clear()
        self.__head.next, self.__tail.prev = self.__tail, self.__head

    class __HashNode:
        def __init__(self, key: int, value: int):
            self.key, self.value, self.prev, self.next = key, value, None, None
