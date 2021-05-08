#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class RadixSort:
    def sort(self, nums: List[int]) -> None:
        maxValue, minValue = max(nums), min(nums)

        diff, gap = maxValue - minValue, 1
        while gap <= diff:
            buckets = [[] for _ in range(10)]
            for value in nums:
                buckets[((value - minValue) // gap) % 10].append(value)

            index = 0
            for bucket in buckets:
                for value in bucket:
                    nums[index] = value
                    index += 1
            gap *= 10
