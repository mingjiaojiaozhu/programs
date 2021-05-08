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

class BellmanFord:
    def search(self, graphs: List[VertexNode], start: int) -> List[int]:
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
