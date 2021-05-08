#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class CountingSort:
    def sort(self, nums: List[int]) -> None:
        maxValue, minValue = max(nums), min(nums)

        size = maxValue - minValue + 1
        buckets = [0 for _ in range(size)]
        for value in nums:
            buckets[value - minValue] += 1
        for i in range(1, size):
            buckets[i] += buckets[i - 1]

        aux = list(nums)
        for value in aux[ : : -1]:
            index = value - minValue
            nums[buckets[index] - 1] = value
            buckets[index] -= 1
