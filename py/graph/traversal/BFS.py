#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class BFS:
    def traverse(self, graphs: List[VertexNode], start: int) -> List[int]:
        visited, queue = [False for _ in range(len(graphs))], [start]
        visited[start] = True

        result = [start]
        while queue:
            index = queue.pop(0)
            edge = graphs[index].next
            while edge:
                edgeIndex = edge.index
                if not visited[edgeIndex]:
                    result.append(edgeIndex)
                    visited[edgeIndex] = True
                    queue.append(edgeIndex)
                edge = edge.next
        return result
