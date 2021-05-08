#!/usr/bin/env python
# -*- coding:gbk -*-

import heapq, sys
from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int, price: int):
        self.index, self.weight, self.price, self.next = index, weight, price, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class Dijkstra:
    def search(self, graphs: List[VertexNode], start: int, end: int) -> List[int]:
        weights = [[0 for _ in range(len(graphs))] for _ in range(len(graphs))]
        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                weights[i][edge.index] = edge.weight
                edge = edge.next

        parent, maxFlow, minCost, offset, result = [], [], [], [0 for _ in range(len(graphs))], [0 for _ in range(2)]
        while self.__search(graphs, start, end, weights, parent, maxFlow, minCost, offset):
            result[0] += maxFlow[end]
            result[1] += maxFlow[end] * (minCost[end] - offset[start] + offset[end])

            index = end
            while index != start:
                weights[parent[index]][index] -= maxFlow[end]
                weights[index][parent[index]] += maxFlow[end]
                index = parent[index]
            for i, value in enumerate(minCost):
                offset[i] += value
        return result

    def __search(self, graphs: List[VertexNode], start: int, end: int, weights: List[List[int]], parent: List[int], maxFlow: List[int], minCost: List[int], offset: List[int]) -> bool:
        parent[ : ], maxFlow[ : ], minCost[ : ] = [-1 for _ in range(len(graphs))], [sys.maxsize for _ in range(len(graphs))], [sys.maxsize for _ in range(len(graphs))]
        minCost[start] = 0

        visited, queue = [False for _ in range(len(graphs))], [self.__HeapNode(start, minCost[start])]
        while queue:
            heap = heapq.heappop(queue)
            index = heap.index
            visited[index], edge = True, graphs[index].next
            while edge:
                edgeIndex = edge.index
                if weights[index][edgeIndex] and not visited[edgeIndex] and minCost[edgeIndex] > minCost[index] + edge.price + offset[index] - offset[edgeIndex]:
                    parent[edgeIndex], maxFlow[edgeIndex], minCost[edgeIndex] = index, min(maxFlow[index], weights[index][edgeIndex]), minCost[index] + edge.price + offset[index] - offset[edgeIndex]
                    heapq.heappush(queue, self.__HeapNode(edgeIndex, minCost[edgeIndex]))
                edge = edge.next
        return sys.maxsize != minCost[end]

    class __HeapNode:
        def __init__(self, index: int, price: int):
            self.index, self.price = index, price

        def __lt__(self, other):
            return self.price < other.price
