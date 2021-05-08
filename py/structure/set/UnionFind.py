#!/usr/bin/env python
# -*- coding:gbk -*-

class UnionFind:
    def __init__(self, degree: int):
        self.__values, self.__weights, self.__length = [-1 for _ in range(degree)], [1 for _ in range(degree)], degree

    def add(self, start: int, end: int) -> None:
        if start < 0 or start >= self.__length or end < 0 or end >= self.__length:
            return

        rootStart, rootEnd = self.__getRoot(start), self.__getRoot(end)
        if rootStart != rootEnd:
            if self.__weights[rootStart] < self.__weights[rootEnd]:
                self.__values[rootEnd] = rootStart
                self.__weights[rootStart] += self.__weights[rootEnd]
            else:
                self.__values[rootStart] = rootEnd
                self.__weights[rootEnd] += self.__weights[rootStart]

    def contains(self, start: int, end: int) -> bool:
        if start >= 0 and start < self.__length and end >= 0 and end < self.__length:
            return self.__getRoot(start) == self.__getRoot(end)
        return False

    def __getRoot(self, value: int) -> int:
        root = value
        while ~self.__values[root]:
            root = self.__values[root]

        while value != root:
            self.__values[value], value = root, self.__values[value]
        return root
