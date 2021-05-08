#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class TopologicalSort:
    def sort(self, graphs: List[VertexNode]) -> List[int]:
        visited, result = [[False for _ in range(len(graphs))] for _ in range(2)], []
        for i in range(len(graphs)):
            if not visited[0][i] and not self.__search(graphs, i, result, visited):
                return []
        result.reverse()
        return result

    def __search(self, graphs: List[VertexNode], start: int, result: List[int], visited: List[List[bool]]) -> bool:
        visited[1][start] = True
        edge = graphs[start].next
        while edge:
            edgeIndex = edge.index
            if visited[1][edgeIndex] or (not visited[0][edgeIndex] and not self.__search(graphs, edgeIndex, result, visited)):
                return False
            edge = edge.next

        visited[0][start], visited[1][start] = True, False
        result.append(start)
        return True
