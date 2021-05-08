#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class BucketSort:
    def sort(self, nums: List[int]) -> None:
        maxValue, minValue = max(nums), min(nums)

        size = (maxValue - minValue) // 10 + 1
        buckets = [[] for _ in range(size)]
        for value in nums:
            buckets[(value - minValue) // 10].append(value)

        index = 0
        for bucket in buckets:
            bucket.sort()

            for value in bucket:
                nums[index] = value
                index += 1
