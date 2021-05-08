#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class CocktailSort:
    def sort(self, nums: List[int]) -> None:
        start, end = 0, len(nums) - 1
        while start < end:
            flag, index = False, 0
            for i in range(start, end):
                if nums[i + 1] < nums[i]:
                    nums[i], nums[i + 1] = nums[i + 1], nums[i]
                    flag, index = True, i

            if not flag:
                break
            end = index

            flag, index = False, 0
            for i in range(end, start, -1):
                if nums[i - 1] > nums[i]:
                    nums[i], nums[i - 1] = nums[i - 1], nums[i]
                    flag, index = True, i

            if not flag:
                break
            start = index
