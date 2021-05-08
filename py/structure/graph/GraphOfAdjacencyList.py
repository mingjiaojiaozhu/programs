#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class GraphOfAdjacencyList:
    def __init__(self):
        self.__graphs, self.__length, self.__capacity = [None for _ in range(64)], 0, 64

    def isEmpty(self) -> bool:
        return not self.__length

    def addEdge(self, index: int, edgeIndex: int, weight: int) -> None:
        if index < 0 or index >= self.__length or edgeIndex < 0 or edgeIndex >= self.__length or index == edgeIndex:
            return

        if not self.__graphs[index].next:
            self.__graphs[index].next = self.__EdgeNode(edgeIndex, weight)
            return

        edge = self.__graphs[index].next
        while edge.next:
            if edgeIndex == edge.index:
                edge.weight = weight
                return
            edge = edge.next
        if edgeIndex == edge.index:
            edge.weight = weight
        else:
            edge.next = self.__EdgeNode(edgeIndex, weight)

    def addVertex(self, value: int) -> None:
        if self.__length >= self.__capacity:
            self.__graphs.extend([None for _ in range(16)])
            self.__capacity += 16

        self.__graphs[self.__length] = self.__VertexNode(value)
        self.__length += 1

    def eraseEdge(self, index: int, edgeIndex: int) -> None:
        if index < 0 or index >= self.__length or edgeIndex < 0 or edgeIndex >= self.__length or index == edgeIndex:
            return

        edge = self.__graphs[index].next
        if not edge:
            return
        if edgeIndex == edge.index:
            self.__graphs[index].next = edge.next
            return

        while edge.next:
            if edgeIndex == edge.next.index:
                edge.next = edge.next.next
                return
            edge = edge.next

    def eraseVertex(self, index: int) -> None:
        if index < 0 or index >= self.__length:
            return

        for i in range(len(self.__graphs)):
            if i != index:
                self.eraseEdge(i, index)

        for i in range(index + 1, self.__length):
            self.__graphs[i - 1] = self.__graphs[i]
        self.__length -= 1
        self.__graphs[self.__length] = None

    def setEdge(self, index: int, edgeIndex: int, weight: int) -> None:
        if index < 0 or index >= self.__length or edgeIndex < 0 or edgeIndex >= self.__length or index == edgeIndex:
            return

        edge = self.__graphs[index].next
        while edge and edgeIndex != edge.index:
            edge = edge.next

        if edge:
            edge.weight = weight

    def setVertex(self, index: int, value: int) -> None:
        if index >= 0 and index < self.__length:
            self.__graphs[index].value = value

    def getEdge(self, index: int, edgeIndex: int) -> int:
        if index < 0 or index >= self.__length or edgeIndex < 0 or edgeIndex >= self.__length or index == edgeIndex:
            return -sys.maxsize

        edge = self.__graphs[index].next
        while edge and edgeIndex != edge.index:
            edge = edge.next

        if edge:
            return edge.weight
        return -sys.maxsize

    def getVertex(self, index: int) -> int:
        if index >= 0 and index < self.__length:
            return self.__graphs[index].value
        return -sys.maxsize

    def clear(self) -> None:
        self.__values, self.__length = [None for _ in range(self.__capacity)], 0

    class __EdgeNode:
        def __init__(self, index: int, weight: int):
            self.index, self.weight, self.next = index, weight, None

    class __VertexNode:
        def __init__(self, value: int):
            self.value, self.next = value, None
