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

class Dinic:
    def search(self, graphs: List[VertexNode], start: int, end: int) -> int:
        weights = [[0 for _ in range(len(graphs))] for _ in range(len(graphs))]
        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                weights[i][edge.index] = edge.weight
                edge = edge.next

        parent, result = [], 0
        while self.__searchOfBFS(graphs, start, end, weights, parent):
            result += self.__searchOfDFS(graphs, start, end, sys.maxsize, weights, parent)
        return result

    def __searchOfBFS(self, graphs: List[VertexNode], start: int, end: int, weights: List[List[int]], parent: List[int]) -> bool:
        parent[ : ], queue = [-1 for _ in range(len(graphs))], [start]
        while queue:
            index = queue.pop(0)
            edge = graphs[index].next
            while edge:
                edgeIndex = edge.index
                if weights[index][edgeIndex] and not ~parent[edgeIndex]:
                    parent[edgeIndex] = index
                    queue.append(edgeIndex)
                edge = edge.next
        return bool(~parent[end])

    def __searchOfDFS(self, graphs: List[VertexNode], start: int, end: int, flow: int, weights: List[List[int]], parent: List[int]) -> int:
        if start == end:
            return flow

        edge = graphs[start].next
        while edge:
            edgeIndex = edge.index
            if weights[start][edgeIndex] and parent[edgeIndex] == start:
                value = self.__searchOfDFS(graphs, edgeIndex, end, min(flow, weights[start][edgeIndex]), weights, parent)
                if value:
                    weights[start][edgeIndex] -= value
                    weights[edgeIndex][start] += value
                    return value
            edge = edge.next
        return 0
