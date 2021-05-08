#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class Hierholzer:
    def search(self, graphs: List[VertexNode]) -> List[int]:
        start = self.__getStart(graphs)
        if not ~start:
            return []

        visited, result = [[False for _ in range(len(graphs))] for _ in range(len(graphs))], []
        self.__search(graphs, start, visited, result)
        result.reverse()
        return result

    def __search(self, graphs: List[VertexNode], start: int, visited: List[List[bool]], result: List[List[int]]) -> None:
        edge = graphs[start].next
        while edge:
            edgeIndex = edge.index
            if not visited[start][edgeIndex]:
                visited[start][edgeIndex] = True
                self.__search(graphs, edgeIndex, visited, result)
            edge = edge.next
        result.append(start)

    def __getStart(self, graphs: List[VertexNode]) -> int:
        inDegrees, outDegrees = [0 for _ in range(len(graphs))], [0 for _ in range(len(graphs))]
        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                inDegrees[edge.index] += 1
                outDegrees[i] += 1
                edge = edge.next

        start, inCount, outCount = 0, 0, 0
        for i, (value1, value2) in enumerate(zip(inDegrees, outDegrees)):
            if abs(value1 - value2) > 1:
                return -1

            if 1 == value2 - value1:
                start = i
                inCount += 1
            elif 1 == value1 - value2:
                outCount += 1
            if inCount > 1 or outCount > 1:
                break
        return start if (not inCount and not outCount) or (1 == inCount and 1 == outCount) else -1
