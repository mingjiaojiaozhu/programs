#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class KnapsackOfMultiple:
    def solution(self, weights: List[int], values: List[int], nums: List[int], target: int) -> int:
        result = [0 for _ in range(target + 1)]
        for weight, value, num in zip(weights, values, nums):
            for i in range(target, weight - 1, -1):
                for j in range(min(num, i // weight) + 1):
                    pivot = result[i - j * weight] + j * value
                    if result[i] < pivot:
                        result[i] = pivot
        return result[-1]
