#!/usr/bin/env python
# -*- coding:gbk -*-

import heapq
from typing import List

class AStar:
    def search(self, graphs: List[List[int]], start: List[int], end: List[int]) -> List[List[int]]:
        visited = [[False for _ in range(len(graphs[0]))] for _ in range(len(graphs))]
        visited[start[0]][start[1]] = True

        queue = [self.__HeapNode(start[0], start[1], 0, self.__getDistance(start[0], start[1], end[0], end[1]), None)]
        while queue:
            heap = heapq.heappop(queue)
            if heap.values[0] == end[0] and heap.values[1] == end[1]:
                result = []
                while heap:
                    result.append(heap.values)
                    heap = heap.parent
                result.reverse()
                return result

            self.__search(graphs, queue, visited, heap, heap.values[0] + 1, heap.values[1], end)
            self.__search(graphs, queue, visited, heap, heap.values[0], heap.values[1] + 1, end)
            self.__search(graphs, queue, visited, heap, heap.values[0] - 1, heap.values[1], end)
            self.__search(graphs, queue, visited, heap, heap.values[0], heap.values[1] - 1, end)
        return []

    def __search(self, graphs: List[List[int]], queue: List[int], visited: List[List[bool]], parent: '__HeapNode', row: int, col: int, end: List[int]) -> None:
        if row >= 0 and row < len(graphs) and col >= 0 and col < len(graphs[0]) and graphs[row][col] and not visited[row][col]:
            heapq.heappush(queue, self.__HeapNode(row, col, parent.index + 1, self.__getDistance(row, col, end[0], end[1]), parent))
            visited[row][col] = True

    def __getDistance(self, row1: int, col1: int, row2: int, col2: int) -> int:
        return abs(row2 - row1) + abs(col2 - col1)

    class __HeapNode:
        def __init__(self, row: int, col: int, index: int, weight: int, parent: '__HeapNode'):
            self.values, self.index, self.weight, self.parent = [row, col], index, weight, parent

        def __lt__(self, other):
            return self.weight < other.weight
