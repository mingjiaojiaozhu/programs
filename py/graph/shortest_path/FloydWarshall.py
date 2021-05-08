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

class FloydWarshall:
    def search(self, graphs: List[VertexNode]) -> List[List[int]]:
        result = [[sys.maxsize for _ in range(len(graphs))] for _ in range(len(graphs))]
        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                result[i][edge.index] = edge.weight
                edge = edge.next
            result[i][i] = 0

        for i in range(len(graphs)):
            for j in range(len(graphs)):
                for k in range(len(graphs)):
                    if sys.maxsize == result[j][i] or sys.maxsize == result[i][k]:
                        continue

                    pivot = result[j][i] + result[i][k]
                    if pivot < result[j][k]:
                        result[j][k] = pivot
        return result
