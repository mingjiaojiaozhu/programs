#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class BubbleSort:
    def sort(self, nums: List[int]) -> None:
        border = len(nums) - 1
        for _ in nums:
            flag, index = False, 0
            for i in range(border):
                if nums[i + 1] < nums[i]:
                    nums[i], nums[i + 1] = nums[i + 1], nums[i]
                    flag, index = True, i

            if not flag:
                break
            border = index
