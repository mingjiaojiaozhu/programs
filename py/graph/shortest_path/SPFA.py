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

class SPFA:
    def search(self, graphs: List[VertexNode], start: int) -> List[int]:
        visited, queue = [False for _ in range(len(graphs))], [start]
        result = [sys.maxsize for _ in range(len(graphs))]
        result[start] = 0

        count = 0
        while queue:
            index = queue.pop(0)
            visited[index] = False

            edge = graphs[index].next
            while edge:
                edgeIndex, edgeWeight = edge.index, edge.weight
                if result[edgeIndex] > result[index] + edgeWeight:
                    result[edgeIndex] = result[index] + edgeWeight
                    if not visited[edgeIndex]:
                        queue.append(edgeIndex)
                        visited[edgeIndex] = True
                        count += 1
                edge = edge.next
            if count >= len(graphs):
                return []
        return result
