#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class Array:
    def __init__(self):
        self.__values, self.__length, self.__capacity = [0 for _ in range(64)], 0, 64

    def isEmpty(self) -> bool:
        return not self.__length

    def add(self, index: int, value: int) -> None:
        if index < 0 or index > self.__length:
            return

        if self.__length >= self.__capacity:
            self.__values.extend([0 for _ in range(16)])
            self.__capacity += 16

        for i in range(self.__length - 1, index - 1, -1):
            self.__values[i + 1] = self.__values[i]
        self.__values[index] = value
        self.__length += 1

    def addHead(self, value: int) -> None:
        if self.__length >= self.__capacity:
            self.__values.extend([0 for _ in range(16)])
            self.__capacity += 16

        for i in range(self.__length - 1, -1, -1):
            self.__values[i + 1] = self.__values[i]
        self.__values[0] = value
        self.__length += 1

    def addTail(self, value: int) -> None:
        if self.__length >= self.__capacity:
            self.__values.extend([0 for _ in range(16)])
            self.__capacity += 16

        self.__values[self.__length] = value
        self.__length += 1

    def erase(self, index: int) -> None:
        if index < 0 or index >= self.__length:
            return

        for i in range(index + 1, self.__length):
            self.__values[i - 1] = self.__values[i]
        self.__length -= 1

    def eraseHead(self, ) -> None:
        if not self.__length:
            return

        for i in range(1, self.__length):
            self.__values[i - 1] = self.__values[i]
        self.__length -= 1

    def eraseTail(self, ) -> None:
        if self.__length:
            self.__length -= 1

    def set(self, index: int, value: int) -> None:
        if index >= 0 and index < self.__length:
            self.__values[index] = value

    def get(self, index: int) -> int:
        if index >= 0 and index < self.__length:
            return self.__values[index]
        return -sys.maxsize

    def reverse(self) -> None:
        start, end = 0, self.__length - 1
        while start < end:
            self.__values[start], self.__values[end] = self.__values[end], self.__values[start]

            start += 1
            end -= 1

    def clear(self) -> None:
        self.__values, self.__length = [0 for _ in range(self.__capacity)], 0
