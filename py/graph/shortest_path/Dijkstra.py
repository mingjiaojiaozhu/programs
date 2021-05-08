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

class Dijkstra:
    def search(self, graphs: List[VertexNode], start: int) -> List[int]:
        visited, queue = [False for _ in range(len(graphs))], [self.__HeapNode(start, 0)]
        result = [sys.maxsize for _ in range(len(graphs))]
        while queue:
            heap = heapq.heappop(queue)
            index, weight = heap.index, heap.weight
            if visited[index]:
                continue

            result[index], visited[index] = weight, True
            edge = graphs[index].next
            while edge:
                edgeIndex, edgeWeight = edge.index, weight + edge.weight
                if not visited[edgeIndex]:
                    heapq.heappush(queue, self.__HeapNode(edgeIndex, edgeWeight))
                edge = edge.next
        return result

    class __HeapNode:
        def __init__(self, index: int, weight: int):
            self.index, self.weight = index, weight

        def __lt__(self, other):
            return self.weight < other.weight
