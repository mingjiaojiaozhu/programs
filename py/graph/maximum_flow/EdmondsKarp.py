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

class EdmondsKarp:
    def search(self, graphs: List[VertexNode], start: int, end: int) -> int:
        weights = [[0 for _ in range(len(graphs))] for _ in range(len(graphs))]
        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                weights[i][edge.index] = edge.weight
                edge = edge.next

        parent, maxFlow, result = [], [sys.maxsize for _ in range(len(graphs))], 0
        while True:
            value = self.__search(graphs, start, end, weights, parent, maxFlow)
            if not ~value:
                break

            index = end
            while index != start:
                weights[parent[index]][index] -= value
                weights[index][parent[index]] += value
                index = parent[index]
            result += value
        return result

    def __search(self, graphs: List[VertexNode], start: int, end: int, weights: List[List[int]], parent: List[int], maxFlow: List[int]) -> int:
        parent[ : ], queue = [-1 for _ in range(len(graphs))], [start]
        while queue:
            index = queue.pop(0)
            edge = graphs[index].next
            while edge:
                edgeIndex = edge.index
                if weights[index][edgeIndex] and not ~parent[edgeIndex]:
                    parent[edgeIndex], maxFlow[edgeIndex] = index, min(weights[index][edgeIndex], maxFlow[index])
                    queue.append(edgeIndex)
                edge = edge.next
        return maxFlow[end] if ~parent[end] else -1
