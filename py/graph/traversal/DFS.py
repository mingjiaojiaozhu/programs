#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class DFS:
    def traverse(self, graphs: List[VertexNode], start: int) -> List[int]:
        visited, stack = [False for _ in range(len(graphs))], [start]
        result = []
        while stack:
            index = stack.pop()
            if visited[index]:
                continue

            result.append(index)
            visited[index] = True

            edge = graphs[index].next
            while edge:
                edgeIndex = edge.index
                if not visited[edgeIndex]:
                    stack.append(edgeIndex)
                edge = edge.next
        return result
