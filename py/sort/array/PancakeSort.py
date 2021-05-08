#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class PancakeSort:
    def sort(self, nums: List[int]) -> None:
        for i in range(len(nums), 0, -1):
            maxIndex = 0
            for j, value in enumerate(nums[ : i + 1]):
                if nums[maxIndex] < value:
                    maxIndex = j
            nums[ : maxIndex + 1] = reversed(nums[ : maxIndex + 1])
            nums[ : i + 1] = reversed(nums[ : i + 1])
