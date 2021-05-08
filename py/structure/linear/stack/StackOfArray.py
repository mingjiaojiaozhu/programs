#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class StackOfArray:
    def __init__(self):
        self.__values, self.__length, self.__capacity = [0 for _ in range(64)], 0, 64

    def isEmpty(self) -> bool:
        return not self.__length

    def push(self, value: int) -> None:
        if self.__length >= self.__capacity:
            self.__values.extend([0 for _ in range(16)])
            self.__capacity += 16

        self.__values[self.__length] = value
        self.__length += 1

    def pop(self) -> int:
        if self.__length:
            self.__length -= 1
            return self.__values[self.__length]
        return -sys.maxsize

    def clear(self) -> None:
        self.__values, self.__length = [0 for _ in range(self.__capacity)], 0
