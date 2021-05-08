#!/usr/bin/env python
# -*- coding:gbk -*-

import sys
from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class Tarjan:
    def search(self, graphs: List[VertexNode]) -> List[List[int]]:
        parent, stack = [-1 for _ in range(len(graphs))], []
        result, aux = [], []
        for i in range(len(graphs)):
            if not ~parent[i]:
                self.__search(graphs, i, parent, stack, result, aux, 0)
        return result

    def __search(self, graphs: List[VertexNode], start: int, parent: List[int], stack: List[int], result: List[List[int]], aux: List[int], count: int) -> int:
        parent[start], minValue = count, count
        stack.append(start)

        edge = graphs[start].next
        while edge:
            edgeIndex = edge.index
            if not ~parent[edgeIndex]:
                count = self.__search(graphs, edgeIndex, parent, stack, result, aux, count + 1)
            edge = edge.next

            if minValue > parent[edgeIndex]:
                minValue = parent[edgeIndex]

        if parent[start] > minValue:
            parent[start] = minValue
            return count

        index = stack.pop()
        while index != start:
            aux.append(index)
            parent[index], index = sys.maxsize, stack.pop()
        aux.append(start)
        parent[start] = sys.maxsize
        result.append(list(aux))
        aux.clear()
        return count
