#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class PriorityQueue:
    def __init__(self):
        self.__values, self.__length, self.__capacity = [0 for _ in range(64)], 0, 64

    def isEmpty(self) -> bool:
        return not self.__length

    def enqueue(self, value: int) -> None:
        if self.__length >= self.__capacity:
            self.__values.extend([0 for _ in range(16)])
            self.__capacity += 16

        child = self.__length
        while child > 0:
            parent = (child - 1) >> 1
            if self.__values[parent] <= value:
                break
            self.__values[child], child = self.__values[parent], parent
        self.__values[child] = value
        self.__length += 1

    def dequeue(self) -> int:
        if not self.__length:
            return -sys.maxsize

        self.__length -= 1
        value, pivot, parent = self.__values[0], self.__values[self.__length], 0
        while True:
            child = (parent << 1) + 1
            if child >= self.__length:
                break

            if child < self.__length - 1 and self.__values[child] > self.__values[child + 1]:
                child += 1
            if self.__values[child] >= pivot:
                break
            self.__values[parent], parent = self.__values[child], child
        self.__values[parent] = pivot
        return value

    def clear(self) -> None:
        self.__values, self.__length = [0 for _ in range(self.__capacity)], 0
