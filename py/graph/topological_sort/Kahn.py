#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class Kahn:
    def sort(self, graphs: List[VertexNode]) -> List[int]:
        inDegrees = [0 for _ in range(len(graphs))]
        for graph in graphs:
            edge = graph.next
            while edge:
                inDegrees[edge.index] += 1
                edge = edge.next

        queue = []
        for i, value in enumerate(inDegrees):
            if not value:
                queue.append(i)

        result = []
        while queue:
            index = queue.pop(0)
            result.append(index)

            edge = graphs[index].next
            while edge:
                edgeIndex = edge.index
                inDegrees[edgeIndex] -= 1
                if not inDegrees[edgeIndex]:
                    queue.append(edgeIndex)
                edge = edge.next
        return result if len(result) == len(graphs) else []
