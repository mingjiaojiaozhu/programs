#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class GraphOfAdjacencyMatrix:
    def __init__(self):
        self.__vertexes, self.__edges, self.__length, self.__capacity = [0 for _ in range(64)], [[0 for _ in range(64)] for _ in range(64)], 0, 64

    def isEmpty(self) -> bool:
        return not self.__length

    def addEdge(self, index: int, edgeIndex: int, weight: int) -> None:
        if index >= 0 and index < self.__length and edgeIndex >= 0 and edgeIndex < self.__length and index != edgeIndex:
            self.__edges[index][edgeIndex] = weight

    def addVertex(self, value: int) -> None:
        if self.__length >= self.__capacity:
            self.__vertexes.extend([0 for _ in range(16)])
            for edge in self.__edges:
                edge.extend([0 for _ in range(16)])
            self.__edges.extend([[0 for _ in range(self.__capacity + 16)] for _ in range(16)])
            self.__capacity += 16

        self.__vertexes[self.__length] = value
        self.__length += 1

    def eraseEdge(self, index: int, edgeIndex: int) -> None:
        if index >= 0 and index < self.__length and edgeIndex >= 0 and edgeIndex < self.__length and index != edgeIndex:
            self.__edges[index][edgeIndex] = 0

    def eraseVertex(self, index: int) -> None:
        if index < 0 or index >= self.__length:
            return

        for i in range(index):
            for j in range(index + 1, self.__length):
                self.__edges[i][j - 1] = self.__edges[i][j]
        for i in range(index + 1, self.__length):
            for j in range(index):
                self.__edges[i - 1][j] = self.__edges[i][j]
            for j in range(index + 1, self.__length):
                self.__edges[i - 1][j - 1] = self.__edges[i][j]

        for i in range(index + 1, self.__length):
            self.__vertexes[i - 1] = self.__vertexes[i]
        self.__length -= 1

    def setEdge(self, index: int, edgeIndex: int, weight: int) -> None:
        if index >= 0 and index < self.__length and edgeIndex >= 0 and edgeIndex < self.__length and index != edgeIndex and self.__edges[index][edgeIndex]:
            self.__edges[index][edgeIndex] = weight

    def setVertex(self, index: int, value: int) -> None:
        if index >= 0 and index < self.__length:
            self.__vertexes[index] = value

    def getEdge(self, index: int, edgeIndex: int) -> int:
        if index >= 0 and index < self.__length and edgeIndex >= 0 and edgeIndex < self.__length and index != edgeIndex and self.__edges[index][edgeIndex]:
            return self.__edges[index][edgeIndex]
        return -sys.maxsize

    def getVertex(self, index: int) -> int:
        if index >= 0 and index < self.__length:
            return self.__vertexes[index]
        return -sys.maxsize

    def clear(self) -> None:
        self.__vertexes, self.__edges, self.__length = [0 for _ in range(self.__capacity)], [[0 for _ in range(self.__capacity)] for _ in range(self.__capacity)], 0
