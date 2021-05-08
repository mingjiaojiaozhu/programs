#!/usr/bin/env python
# -*- coding:gbk -*-

import sys
from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int, price: int):
        self.index, self.weight, self.price, self.next = index, weight, price, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class BellmanFord:
    def search(self, graphs: List[VertexNode], start: int, end: int) -> List[int]:
        weights = [[0 for _ in range(len(graphs))] for _ in range(len(graphs))]
        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                weights[i][edge.index] = edge.weight
                edge = edge.next

        parent, maxFlow, minCost, result = [], [], [], [0 for _ in range(2)]
        while self.__search(graphs, start, end, weights, parent, maxFlow, minCost):
            result[0] += maxFlow[end]
            result[1] += maxFlow[end] * minCost[end]

            index = end
            while index != start:
                weights[parent[index]][index] -= maxFlow[end]
                weights[index][parent[index]] += maxFlow[end]
                index = parent[index]
        return result

    def __search(self, graphs: List[VertexNode], start: int, end: int, weights: List[List[int]], parent: List[int], maxFlow: List[int], minCost: List[int]) -> bool:
        parent[ : ], maxFlow[ : ], minCost[ : ] = [-1 for _ in range(len(graphs))], [sys.maxsize for _ in range(len(graphs))], [sys.maxsize for _ in range(len(graphs))]
        minCost[start] = 0

        index = start
        for _ in graphs:
            edge = graphs[index].next
            while edge:
                edgeIndex = edge.index
                if weights[index][edgeIndex] and minCost[edgeIndex] > minCost[index] + edge.price:
                    parent[edgeIndex], maxFlow[edgeIndex], minCost[edgeIndex] = index, min(maxFlow[index], weights[index][edgeIndex]), minCost[index] + edge.price
                edge = edge.next

            index += 1
            if index >= len(graphs):
                index = 0
        return sys.maxsize != minCost[end]
