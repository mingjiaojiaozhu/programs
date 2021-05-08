#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class KnapsackOfZeroOne:
    def solution(self, weights: List[int], values: List[int], target: int) -> int:
        result = [0 for _ in range(target + 1)]
        for weight, value in zip(weights, values):
            for i in range(target, weight - 1, -1):
                pivot = result[i - weight] + value
                if result[i] < pivot:
                    result[i] = pivot
        return result[-1]
