#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class CriticalPath:
    def search(self, graphs: List[VertexNode]) -> List[int]:
        stack = []
        vertexEnd = self.__topologicalSort(graphs, stack)
        if not vertexEnd:
            return []
        vertexLatest = self.__reverseTopologicalSort(graphs, vertexEnd, stack)

        result = []
        for i, (value1, value2) in enumerate(zip(vertexEnd, vertexLatest)):
            if value1 == value2:
                result.append(i)
        return result

    def __topologicalSort(self, graphs: List[VertexNode], stack: List[int]) -> List[int]:
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

        vertexEnd, count = [0 for _ in range(len(graphs))], 0
        while queue:
            index = queue.pop(0)
            stack.append(index)
            count += 1

            edge, pivot = graphs[index].next, vertexEnd[index]
            while edge:
                edgeIndex, edgeWeight = edge.index, edge.weight
                inDegrees[edgeIndex] -= 1
                if not inDegrees[edgeIndex]:
                    queue.append(edgeIndex)
                    if vertexEnd[edgeIndex] < pivot + edgeWeight:
                        vertexEnd[edgeIndex] = pivot + edgeWeight
                edge = edge.next
        return vertexEnd if count == len(graphs) else []

    def __reverseTopologicalSort(self, graphs: List[VertexNode], vertexEnd: List[int], stack: List[int]) -> List[int]:
        maxValue = vertexEnd[stack.pop()]
        vertexLatest = [maxValue for _ in range(len(graphs))]
        while stack:
            index = stack.pop()
            edge = graphs[index].next
            while edge:
                edgeIndex, edgeWeight = edge.index, edge.weight
                if vertexLatest[index] > vertexLatest[edgeIndex] - edgeWeight:
                    vertexLatest[index] = vertexLatest[edgeIndex] - edgeWeight
                edge = edge.next
        return vertexLatest
