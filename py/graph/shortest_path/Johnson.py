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

class Johnson:
    def search(self, graphs: List[VertexNode]) -> List[List[int]]:
        aux = list(graphs)
        aux.append(VertexNode(0))
        for i in range(len(graphs) - 1, -1, -1):
            edge = EdgeNode(i, 0)
            edge.next, aux[-1].next = aux[-1].next, edge

        reWeight = self.__bellmanFord(aux, len(graphs))
        if not reWeight:
            return []

        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                edge.weight += reWeight[i] - reWeight[edge.index]
                edge = edge.next

        result = []
        for i in range(len(graphs)):
            result.append(self.__dijkstra(graphs, i))
            for j in range(len(graphs)):
                if sys.maxsize != result[i][j]:
                    result[i][j] += reWeight[j] - reWeight[i]
        return result

    def __bellmanFord(self, graphs: List[VertexNode], start: int) -> List[int]:
        result = [sys.maxsize for _ in range(len(graphs))]
        result[start] = 0

        index = start
        for _ in graphs:
            edge = graphs[index].next
            while edge:
                pivot, edgeIndex = result[index] + edge.weight, edge.index
                if sys.maxsize != result[index] and pivot < result[edgeIndex]:
                    result[edgeIndex] = pivot
                edge = edge.next

            index += 1
            if index >= len(graphs):
                index = 0

        index = start
        for _ in graphs:
            edge = graphs[index].next
            while edge:
                pivot, edgeIndex = result[index] + edge.weight, edge.index
                if sys.maxsize != result[index] and pivot < result[edgeIndex]:
                    return []
                edge = edge.next

            index += 1
            if index >= len(graphs):
                index = 0
        return result

    def __dijkstra(self, graphs: List[VertexNode], start: int) -> List[int]:
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
