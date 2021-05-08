#!/usr/bin/env python
# -*- coding:gbk -*-

import sys
from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class SAP:
    def search(self, graphs: List[VertexNode], start: int, end: int) -> int:
        weights = [[0 for _ in range(len(graphs))] for _ in range(len(graphs))]
        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                weights[i][edge.index] = edge.weight
                edge = edge.next

        gap, degrees, result = [0 for _ in range(len(graphs) + 1)], [0 for _ in range(len(graphs))], 0
        gap[0] = len(graphs)
        while degrees[start] != len(graphs):
            result += self.__search(graphs, start, end, start, sys.maxsize, weights, gap, degrees)
        return result

    def __search(self, graphs: List[VertexNode], start: int, end: int, index: int, flow: int, weights: List[List[int]], gap: List[int], degrees: List[int]) -> int:
        if index == end:
            return flow

        edge, pivot, border = graphs[index].next, flow, len(graphs) - 1
        while edge:
            edgeIndex = edge.index
            if weights[index][edgeIndex]:
                if degrees[index] == degrees[edgeIndex] + 1:
                    value = self.__search(graphs, start, end, edgeIndex, min(pivot, weights[index][edgeIndex]), weights, gap, degrees)
                    weights[index][edgeIndex] -= value
                    weights[edgeIndex][index] += value
                    pivot -= value
                    if degrees[start] == len(graphs) or not pivot:
                        return flow - pivot
                if border > degrees[edgeIndex]:
                    border = degrees[edgeIndex]
            edge = edge.next

        gap[degrees[index]] -= 1
        if not ~gap[degrees[index]]:
            degrees[start] = len(graphs)
        else:
            degrees[index] = border + 1
            gap[degrees[index]] += 1
        return flow - pivot
