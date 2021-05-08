#!/usr/bin/env python
# -*- coding:gbk -*-

import heapq
from typing import List

class OptimalLoading:
    def solution(self, weights: List[int], target: int) -> List[int]:
        aux = [0 for _ in range(len(weights))]
        for i in range(len(weights) - 1, 0, -1):
            aux[i - 1] = aux[i] + weights[i]

        queue, weight, level, current = [], 0, 0, None
        while level != len(weights):
            if weight + weights[level] <= target:
                heapq.heappush(queue, self.__HeapNode(weight + weights[level] + aux[level], level + 1, current, True))
            heapq.heappush(queue, self.__HeapNode(weight + aux[level], level + 1, current, False))

            current = heapq.heappop(queue)
            level = current.level
            weight = current.weight - aux[level - 1]

        result = []
        for value in weights[ : : -1]:
            if current.marked:
                result.append(value)
            current = current.parent
        result.reverse()
        return result

    class __HeapNode:
        def __init__(self, weight: int, level: int, parent: '__HeapNode', marked: bool):
            self.weight, self.level, self.parent, self.marked = weight, level, parent, marked

        def __lt__(self, other):
            return self.weight > other.weight
