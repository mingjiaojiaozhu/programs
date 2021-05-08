#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class BinarySearch:
    def search(self, nums: List[int], target: int) -> int:
        start, end = 0, len(nums) - 1
        while start <= end:
            middle = start + ((end - start) >> 1)
            if target == nums[middle]:
                return middle

            if target < nums[middle]:
                end = middle - 1
            else:
                start = middle + 1
        return -1
