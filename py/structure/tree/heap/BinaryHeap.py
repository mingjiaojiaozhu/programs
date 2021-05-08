#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class BinaryHeap:
    def __init__(self):
        self.__values, self.__length, self.__capacity = [0 for _ in range(64)], 0, 64

    def isEmpty(self) -> bool:
        return not self.__length

    def add(self, value: int) -> None:
        if self.__length >= self.__capacity:
            aux = [0 for _ in range(self.__capacity + 16)]
            aux[ : self.__capacity] = self.__values[ : ]
            self.__values = aux
            self.__capacity += 16

        self.__adjustHeapUp(self.__length, value)
        self.__length += 1

    def erase(self, index: int) -> None:
        if index >= 0 and index < self.__length:
            self.__length -= 1
            self.__adjustHeapDown(index, self.__values[self.__length])

    def set(self, index: int, value: int) -> None:
        if index >= 0 and index < self.__length and value != self.__values[index]:
            if value < self.__values[index]:
                self.__adjustHeapUp(index, value)
            else:
                self.__adjustHeapDown(index, value)

    def get(self, index: int) -> int:
        if index >= 0 and index < self.__length:
            return self.__values[index]
        return -sys.maxsize

    def clear(self) -> None:
        self.__values, self.__length = [0 for _ in range(self.__capacity)], 0

    def __adjustHeapUp(self, child: int, pivot: int) -> None:
        while child > 0:
            parent = (child - 1) >> 1
            if self.__values[parent] <= pivot:
                break
            self.__values[child], child = self.__values[parent], parent
        self.__values[child] = pivot

    def __adjustHeapDown(self, parent: int, pivot: int) -> None:
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
