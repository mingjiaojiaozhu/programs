#!/usr/bin/env python
# -*- coding:gbk -*-

import heapq
from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class Prim:
    def search(self, graphs: List[VertexNode], start: int) -> List[int]:
        visited, queue = [False for _ in range(len(graphs))], [self.__HeapNode(-1, start, 0)]
        result = [-1 for _ in range(len(graphs))]
        while queue:
            heap = heapq.heappop(queue)
            fromIndex, toIndex = heap.fromIndex, heap.toIndex
            if visited[toIndex]:
                continue

            result[toIndex], visited[toIndex] = fromIndex, True
            edge = graphs[toIndex].next
            while edge:
                edgeIndex, edgeWeight = edge.index, edge.weight
                if not visited[edgeIndex]:
                    heapq.heappush(queue, self.__HeapNode(toIndex, edgeIndex, edgeWeight))
                edge = edge.next
        return result

    class __HeapNode:
        def __init__(self, fromIndex: int, toIndex: int, weight: int):
            self.fromIndex, self.toIndex, self.weight = fromIndex, toIndex, weight

        def __lt__(self, other):
            return self.weight < other.weight
