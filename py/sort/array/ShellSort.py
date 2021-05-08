#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class ShellSort:
    def sort(self, nums: List[int]) -> None:
        gap = 1
        while gap < len(nums) // 3:
            gap = gap * 3 + 1

        while gap > 0:
            for i, value in enumerate(nums[gap : ]):
                pivot, index = value, i
                while index >= 0 and nums[index] > pivot:
                    nums[index + gap] = nums[index]
                    index -= gap
                nums[index + gap] = pivot
            gap //= 3
