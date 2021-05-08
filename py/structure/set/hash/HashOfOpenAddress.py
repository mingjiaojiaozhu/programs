#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class HashOfOpenAddress:
    def __init__(self):
        self.__hash = [self.__HashNode(0, 0) for _ in range(256)]

    def isEmpty(self) -> bool:
        for node in self.__hash:
            if node.used:
                return False
        return True

    def add(self, key: int, value: int) -> None:
        index = key % 256
        for _ in range(256):
            current = self.__hash[index]
            if current.used and key == current.key:
                current.value = value
                return

            if not current.used:
                current.key, current.value, current.used = key, value, True
                return

            index += 1
            if index >= 256:
                index = 0

    def erase(self, key: int) -> None:
        index = key % 256
        for _ in range(256):
            current = self.__hash[index]
            if current.used and key == current.key:
                current.key, current.value, current.used = 0, 0, False
                return

            index += 1
            if index >= 256:
                index = 0

    def set(self, key: int, value: int) -> None:
        index = key % 256
        for _ in range(256):
            current = self.__hash[index]
            if current.used and key == current.key:
                current.value = value
                return

            index += 1
            if index >= 256:
                index = 0

    def get(self, key: int) -> int:
        index = key % 256
        for _ in range(256):
            current = self.__hash[index]
            if current.used and key == current.key:
                return current.value

            index += 1
            if index >= 256:
                index = 0
        return -sys.maxsize

    def clear(self) -> None:
        for node in self.__hash:
            node.key, node.value, node.used = 0, 0, False

    class __HashNode:
        def __init__(self, key: int, value: int):
            self.key, self.value, self.used = key, value, False
