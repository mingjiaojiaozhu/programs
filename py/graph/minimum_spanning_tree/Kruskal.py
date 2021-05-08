#!/usr/bin/env python
# -*- coding:gbk -*-

import functools
from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class Kruskal:
    def search(self, graphs: List[VertexNode]) -> List[int]:
        edgeLists = []
        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                edgeLists.append(self.__ConnectedNode(i, edge.index, edge.weight))
                edge = edge.next

        edgeLists.sort(key = functools.cmp_to_key(self.__cmp))

        roots, visited = [-1 for _ in range(len(graphs))], [False for _ in range(len(graphs))]
        result = [-1 for _ in range(len(graphs))]
        for edge in edgeLists:
            fromIndex, toIndex = edge.fromIndex, edge.toIndex
            if not visited[toIndex] and self.__getRoot(roots, fromIndex) != self.__getRoot(roots, toIndex):
                result[toIndex], roots[fromIndex], visited[toIndex] = fromIndex, toIndex, True
        return result

    def __getRoot(self, roots: List[int], index: int) -> None:
        while ~roots[index]:
            index = roots[index]
        return index

    def __cmp(self, node1: '__ConnectedNode', node2: '__ConnectedNode') -> int:
        return node1.weight - node2.weight

    class __ConnectedNode:
        def __init__(self, fromIndex: int, toIndex: int, weight: int):
            self.fromIndex, self.toIndex, self.weight = fromIndex, toIndex, weight
