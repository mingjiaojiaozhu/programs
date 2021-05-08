#!/usr/bin/env python
# -*- coding:gbk -*-

import heapq, sys
from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class HLPP:
    def search(self, graphs: List[VertexNode], start: int, end: int) -> int:
        weights = [[0 for _ in range(len(graphs))] for _ in range(len(graphs))]
        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                weights[i][edge.index] = edge.weight
                edge = edge.next

        gap, degrees, queue, result = [0 for _ in range(len(graphs))], [0 for _ in range(len(graphs))], [], [0 for _ in range(len(graphs))]
        degrees[start], result[start] = len(graphs), sys.maxsize

        edge = graphs[start].next
        while edge:
            edgeIndex = edge.index
            value = min(result[start], weights[start][edgeIndex])
            weights[start][edgeIndex] -= value
            weights[edgeIndex][start] += value
            result[start] -= value
            result[edgeIndex] += value
            if value and edgeIndex != end:
                heapq.heappush(queue, self.__HeapNode(edgeIndex, degrees[edgeIndex]))
            edge = edge.next

        while queue:
            heap = heapq.heappop(queue)
            index = heap.index
            if result[index]:
                self.__search(graphs, index, end, weights, gap, degrees, queue, result)
        return result[end]

    def __search(self, graphs: List[VertexNode], start: int, end: int, weights: List[List[int]], gap: List[int], degrees: List[int], queue: List[int], result: List[int]) -> None:
        edge = graphs[start].next
        while edge:
            edgeIndex = edge.index
            if degrees[start] == degrees[edgeIndex] + 1:
                value = min(result[start], weights[start][edgeIndex])
                weights[start][edgeIndex] -= value
                weights[edgeIndex][start] += value
                result[start] -= value
                result[edgeIndex] += value
                if value and edgeIndex != end:
                    heapq.heappush(queue, self.__HeapNode(edgeIndex, degrees[edgeIndex]))
            edge = edge.next

        if start != end and result[start]:
            gap[degrees[start]] -= 1
            if not ~gap[degrees[start]]:
                for i in range(len(graphs)):
                    if i != end and degrees[i] > degrees[start] and degrees[i] < len(graphs):
                        degrees[i] = len(graphs)
            degrees[start] += 1
            if degrees[start] < len(graphs):
                gap[degrees[start]] += 1
                heapq.heappush(queue, self.__HeapNode(start, degrees[start]))

    class __HeapNode:
        def __init__(self, index: int, degree: int):
            self.index, self.degree = index, degree

        def __lt__(self, other):
            return self.degree > other.degree
