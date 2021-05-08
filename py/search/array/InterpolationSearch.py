#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class InterpolationSearch:
    def search(self, nums: List[int], target: int) -> int:
        start, end = 0, len(nums) - 1
        while start < end and nums[start] != nums[end]:
            middle = start + (target - nums[start]) * (end - start) // (nums[end] - nums[start])
            if middle < start or middle > end:
                return -1

            if target == nums[middle]:
                return middle

            if target < nums[middle]:
                end = middle - 1
            else:
                start = middle + 1
        return start if start < len(nums) and target == nums[start] else -1
