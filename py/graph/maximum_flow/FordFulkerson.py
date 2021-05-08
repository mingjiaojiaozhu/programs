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

class FordFulkerson:
    def search(self, graphs: List[VertexNode], start: int, end: int) -> int:
        weights = [[0 for _ in range(len(graphs))] for _ in range(len(graphs))]
        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                weights[i][edge.index] = edge.weight
                edge = edge.next

        parent, result = [-1 for _ in range(len(graphs))], 0
        while self.__search(graphs, start, end, weights, parent):
            value, index = sys.maxsize, end
            while index != start:
                if value > weights[parent[index]][index]:
                    value = weights[parent[index]][index]
                index = parent[index]

            index = end
            while index != start:
                weights[parent[index]][index] -= value
                weights[index][parent[index]] += value
                index = parent[index]
            result += value
        return result

    def __search(self, graphs: List[VertexNode], start: int, end: int, weights: List[List[int]], parent: List[int]) -> bool:
        visited, queue = [False for _ in range(len(graphs))], [start]
        visited[start] = True
        while queue:
            index = queue.pop(0)
            edge = graphs[index].next
            while edge:
                edgeIndex = edge.index
                if not visited[edgeIndex] and weights[index][edgeIndex]:
                    parent[edgeIndex], visited[edgeIndex] = index, True
                    queue.append(edgeIndex)
                edge = edge.next
        return visited[end]
