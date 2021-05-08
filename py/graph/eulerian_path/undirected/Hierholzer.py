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
                visited[start][edgeIndex], visited[edgeIndex][start] = True, True
                self.__search(graphs, edgeIndex, visited, result)
            edge = edge.next
        result.append(start)

    def __getStart(self, graphs: List[VertexNode]) -> int:
        start, oddCount = 0, 0
        for i in range(len(graphs) - 1, -1, -1):
            count, edge = 0, graphs[i].next
            while edge:
                count += 1
                edge = edge.next
            if count & 1:
                start = i
                oddCount += 1
                if oddCount > 2:
                    break
        return start if not oddCount or 2 == oddCount else -1
