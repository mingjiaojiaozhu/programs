#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class GnomeSort:
    def sort(self, nums: List[int]) -> None:
        index = 0
        while index < len(nums):
            if not index or nums[index - 1] <= nums[index]:
                index += 1
            else:
                nums[index], nums[index - 1] = nums[index - 1], nums[index]
                index -= 1
